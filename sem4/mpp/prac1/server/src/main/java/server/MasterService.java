package server;

import domain.*;
import repository.GameRepository;
import repository.MoveRepository;
import repository.WordsRepository;
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
	private final WordsRepository wordsRepository;
	private final MoveRepository moveRepository;

	private final Map<String, IUserObserver> loggedClients;

	public MasterService(LoginService loginService, GameRepository gameRepository, WordsRepository wordsRepository, MoveRepository moveRepository) {
		this.loginService = loginService;
		this.gameRepository = gameRepository;
		this.wordsRepository = wordsRepository;
		this.moveRepository = moveRepository;
		loggedClients = new ConcurrentHashMap<>();
	}

	@Override
	public synchronized void register(String username, String password) {
		loginService.register(username, password);
	}

	@Override
	public synchronized void logIn(String username, String password, IUserObserver user) throws Exception {
		if (loggedClients.get(username) != null)
			throw new Exception("User already logged in.");
		loginService.login(username, password);
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

	private String generateConfiguration() {
		List<Word> words = (List<Word>) wordsRepository.getAll();
		Collections.shuffle(words);
		words = words.stream().limit(nr).toList();
		List<Word> config = new ArrayList<>();
		for (Word word : words) {
			config.add(word);
			config.add(word);
		}
		Collections.shuffle(config);
		String result = "";
		for (Word word : config)
			result += word.getWord() + ' ';
		return result.substring(0, result.length() - 1);
	}

	public void endGame(Game game) {
		game = gameRepository.getById(game.getId());
		int duration = game.getDuration();
		duration += (int) Instant.now().getEpochSecond();
		game.setDuration(duration);
		gameRepository.update(game, game.getId());
	}

	@Override
	public Game startGame(String user) {
		Game game = new Game();
		game.setUser(user);
		game.setDuration(-(int) Instant.now().getEpochSecond());
		game.setConfiguration(generateConfiguration());
		return gameRepository.add(game);
	}

	public boolean hasEnded(Game game) {
		if (game.getMoves().size() == 10)
			return true;
		int match = 0;
		for (Move move : game.getMoves()) {
			String word1 = getWordConfiguration(game.getConfiguration(), move.getPos1());
			String word2 = getWordConfiguration(game.getConfiguration(), move.getPos2());
			if (word1.equals(word2))
				++match;
		}
//		System.out.println("MATCHES: " + String.valueOf(match));
		return match == 5;
	}

	@Override
	public MoveReply move(Move move) throws Exception {
		moveRepository.add(move);
		int gameId = move.getGame().getId();
		Game game = gameRepository.getById(gameId);
		int points = game.getPoints();
		String word1 = getWordConfiguration(game.getConfiguration(), move.getPos1());
		String word2 = getWordConfiguration(game.getConfiguration(), move.getPos2());
		if (word1.equals(word2))
			points -= 2;
		else
			points += 3;
		game.setPoints(points);
		gameRepository.update(game, gameId);
		MoveReply moveReply = new MoveReply();
		moveReply.setWord1(word1);
		moveReply.setWord2(word2);
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

	public void changeConfiguration(Game game, String configuration) {
		game.setConfiguration(configuration);
		gameRepository.update(game,game.getId());
	}
}
