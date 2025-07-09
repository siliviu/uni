package server;

import domain.*;
import repository.ConfigurationRepo;
import repository.GameRepository;
import repository.MoveRepository;
import services.IMasterService;
import services.IUserObserver;

import java.time.Instant;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import utils.HibernateUtils;

public class MasterService implements IMasterService {
	private final LoginService loginService;
	private final GameRepository gameRepository;
	private final ConfigurationRepo configurationRepo;
	private final MoveRepository moveRepository;

	private final Map<String, IUserObserver> loggedClients;

	public MasterService(LoginService loginService, GameRepository gameRepository, ConfigurationRepo configurationRepo, MoveRepository moveRepository) {
		this.loginService = loginService;
		this.gameRepository = gameRepository;
		this.configurationRepo = configurationRepo;
		this.moveRepository = moveRepository;
		loggedClients = new ConcurrentHashMap<>();
	}

	@Override
	public synchronized void register(String username) {
		loginService.register(username);
	}

	@Override
	public synchronized void logIn(String username, IUserObserver user) throws Exception {
		if (loggedClients.get(username) != null)
			throw new Exception("User already logged in.");
		loginService.login(username);
		loggedClients.put(username, user);
	}

	@Override
	public void logOut(IUserObserver observer) throws Exception {
		String username = null;
		for (Map.Entry<String, IUserObserver> entry : loggedClients.entrySet())
			if (Objects.equals(observer, entry.getValue()))
				username = entry.getKey();
		if (username == null)
			throw new Exception("User not logged in");
		loggedClients.remove(username);
		HibernateUtils.closeSessionFactory();
	}


	private final int nr = 5;

	private String getWordConfiguration(String configuration, int pos) {
		String[] arrOfStr = configuration.split(" ");
		return arrOfStr[pos - 1];
	}

	private Configuration generateConfiguration() {
		List<Configuration> configurations = (List<Configuration>) configurationRepo.getAll();
		Collections.shuffle(configurations);
		return configurations.get(0);
	}

	public void endGame(Game game) {
		game = gameRepository.getById(game.getId());
		game.setStart((int) Instant.now().getEpochSecond());
		gameRepository.update(game, game.getId());
	}

	@Override
	public Game startGame(String user) {
		Game game = new Game();
		game.setUser(user);
		game.setConfiguration(generateConfiguration());
		return gameRepository.add(game);
	}

	public boolean hasEnded(Game game) {
		return game.getMoves().size() == 4;
	}

	public int getPoints(String guess, Configuration configuration, MoveReply moveReply) {
		ArrayList<String> words = new ArrayList<>();
		words.add(configuration.getWord1());
		words.add(configuration.getWord2());
		words.add(configuration.getWord3());
		words.add(configuration.getWord4());
		int maxPoints = 0;
		for (String word : words) {
			if (guess.equals(word)) {
				moveReply.setCorrect(true);
				return word.length();
			}
			int j = Math.min(word.length(), guess.length());
			int curpoints = 0;
			for (int i = 0; i < j; ++i)
				if (word.charAt(i) == guess.charAt(i))
					++curpoints;
			maxPoints = Math.max(maxPoints, curpoints);
		}
		moveReply.setCorrect(false);
		return maxPoints;
	}

	@Override
	public MoveReply move(Move move) throws Exception {
		moveRepository.add(move);
		int gameId = move.getGame().getId();
		Game game = gameRepository.getById(gameId);
		int points = game.getPoints();
		String guess = move.getWord();
		MoveReply moveReply = new MoveReply();
		points += getPoints(guess, game.getConfiguration(), moveReply);
		game.setPoints(points);
		gameRepository.update(game, gameId);
		if (hasEnded(game)) {
			System.out.println("GAME ENDED");
			moveReply.setGame(game);
			moveReply.setEnded(true);
			endGame(game);
			notifyUpdate();
		}
		return moveReply;
	}

	@Override
	public List<Game> getLeaderboard() throws Exception {
		return (List<Game>) gameRepository.getLeaderboard();
	}

//	@Override
//	public synchronized List<ChildDTO> searchChildren(RaceDistance raceDistance, AgeGroup ageGroup) {
//		return userService.searchChildren(raceDistance, ageGroup);
//	}
//
//	@Override
//	public synchronized void signUpChild(String name, Integer age, RaceDistance raceDistance, AgeGroup ageGroup) {
//		userService.signUpChild(name, age, raceDistance, ageGroup);
//		notifySignup();
//	}


	private final int defaultThreadsNo = 5;

	private void notifyUpdate() {
		System.out.println("Notifying");

		ExecutorService executor = Executors.newFixedThreadPool(defaultThreadsNo);
		for (IUserObserver user : loggedClients.values())
			if (user != null)
				executor.execute(() -> {
					try {
						System.out.println("Notifying " + user);
						user.notifyUpdate();
					} catch (Exception e) {
						System.err.println("Error notifying friend " + e);
					}
				});
		executor.shutdown();
	}

	public Game getGame(Integer id) {
		return gameRepository.getById(id);
	}

	public void changeConfiguration(Game game, Configuration configuration) {
//		game.setConfiguration(configuration);
		gameRepository.update(game, game.getId());
	}

	public boolean isWordGuessed(String word, Configuration configuration) {
		return word.equals(configuration.getWord1()) || word.equals(configuration.getWord2()) || word.equals(configuration.getWord3()) || word.equals(configuration.getWord4());
	}

	public Configuration addConfiguration(Configuration configuration) {
		return configurationRepo.add(configuration);
	}

	public List<Game> getGuesses(String user) throws Exception {
		List<Game> games = (List<Game>) gameRepository.getGames(user);
		List<Game> answer = new ArrayList<>();
		for (Game game : games) {
			int guessed = 0;
			for (Move move : game.getMoves())
				if (isWordGuessed(move.getWord(), game.getConfiguration()))
					guessed += 1;
			if (guessed >= 2)
				answer.add(game);
		}
		return answer;
	}
}
