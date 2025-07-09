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
	//	private final WordsRepository wordsRepository;
	private final MoveRepository moveRepository;

	private final Map<String, IUserObserver> loggedClients;

	public MasterService(LoginService loginService, GameRepository gameRepository, MoveRepository moveRepository) {
		this.loginService = loginService;
		this.gameRepository = gameRepository;
//		this.wordsRepository = wordsRepository;
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


	private final int nr = 3;

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
		return gameRepository.add(game);
	}

	public boolean hasEnded(Game game, MoveReply moveReply) {

		int[][] board = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};

		int match = 0;
		for (Move move : game.getMoves()) {
			int y = move.getY() - 1;
			int x = move.getX() - 1;
			if (move.isPlayer())
				board[y][x] = 1;
			else
				board[y][x] = 0;
		}
		for (int i = 0; i < 2; ++i) {
			moveReply.setWinner(i == 0 ? "Computer" : "Player");
			if (board[0][0] == i && board[0][0] == board[0][1] && board[0][0] == board[0][2])
				return true;
			if (board[0][0] == i && board[0][0] == board[1][0] && board[0][0] == board[2][0])

				return true;
			if (board[0][0] == i && board[0][0] == board[1][1] && board[0][0] == board[2][2])
				return true;

			if (board[2][2] == i && board[2][2] == board[1][2] && board[2][2] == board[0][2])
				return true;
			if (board[2][2] == i && board[2][2] == board[2][1] && board[2][2] == board[2][0])
				return true;

			if (board[0][2] == i && board[0][2] == board[1][1] && board[0][2] == board[2][0])
				return true;

			if (board[1][1] == i && board[1][1] == board[0][1] && board[1][1] == board[2][1])
				return true;
			if (board[1][1] == i && board[1][1] == board[1][0] && board[1][1] == board[1][2])
				return true;
		}
		if (game.getMoves().size() == 9) {
			moveReply.setWinner("Draw");
			return true;
		}
		moveReply.setWinner("");
		return false;
	}


	public boolean isGood(Game game, int y, int x) {
		for (Move move : game.getMoves())
			if (move.getY() == y && move.getX() == x)
				return false;
		return true;
	}

	@Override
	public MoveReply move(Move move) throws Exception {
		moveRepository.add(move);
		int gameId = move.getGame().getId();
		Game game = gameRepository.getById(gameId);
		MoveReply moveReply = new MoveReply();
		if (hasEnded(game, moveReply)) {
			moveReply.setY(0);
			moveReply.setGame(game);
			moveReply.setEnded(true);
			int points = game.getPoints();
			if (moveReply.getWinner().equals("Draw"))
				points += 5;
			else if (moveReply.getWinner().equals("Player"))
				points += 10;
			game.setPoints(points);
			gameRepository.update(game, gameId);
			endGame(game);
			notifyUpdate();
			return moveReply;
		}
		Random random = new Random();
		int y, x;
		do {
			y = random.nextInt(1, 4);
			x = random.nextInt(1, 4);
		} while (!isGood(game, y, x));
		Move computerMove = new Move();
		computerMove.setY(y);
		computerMove.setX(x);
		computerMove.setGame(game);
		moveRepository.add(computerMove);

		game = gameRepository.getById(gameId);
		moveReply.setY(y);
		moveReply.setX(x);
		if (hasEnded(game, moveReply)) {
			System.out.println("GAME ENDED");
			moveReply.setGame(game);
			moveReply.setEnded(true);
			int points = game.getPoints();
			if (moveReply.getWinner().equals("Computer"))
				points -= 10;
			game.setPoints(points);
			gameRepository.update(game, gameId);
			endGame(game);
			notifyUpdate();
			return moveReply;
		}
		return moveReply;
	}

	@Override
	public List<Game> getLeaderboard() throws Exception {
		return (List<Game>) gameRepository.getLeaderboard();
	}

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
//		game.setConfiguration(configuration);
		gameRepository.update(game, game.getId());
	}
}
