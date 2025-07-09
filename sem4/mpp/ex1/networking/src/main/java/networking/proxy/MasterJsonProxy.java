package networking.proxy;

import domain.*;
import networking.Request;
import networking.RequestType;
import networking.Response;
import networking.ResponseType;
import services.IMasterService;
import services.IUserObserver;

import java.util.List;

public class MasterJsonProxy extends AbstractJsonProxy implements IMasterService {

	private IUserObserver user;

	public MasterJsonProxy(String host, int port) {
		super(host, port);
	}

	protected boolean isUpdate(Response response) {
		return response.getType() == ResponseType.UPDATE;
	}

	protected void handleUpdate(Response response) {
		if (response.getType() == ResponseType.UPDATE) {
			try {
				user.notifyUpdate();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	@Override
	public void register(String username) throws Exception {
		initializeConnection();
		Request req = new Request();
		req.setUser(new User(username));
		req.setType(RequestType.REGISTER);
		sendRequest(req);
		Response response = getResponse();
		if (response.getType() == ResponseType.ERROR) {
//			closeConnection();
			String err = response.getErrorMessage();
			throw new Exception(err);
		}
	}

	@Override
	public void logIn(String username, IUserObserver user) throws Exception {
		initializeConnection();
		Request req = new Request();
		req.setUser(new User(username));
		req.setType(RequestType.LOGIN);
		sendRequest(req);
		Response response = getResponse();
		if (response.getType() == ResponseType.OK) {
			this.user = user;
			return;
		}
		if (response.getType() == ResponseType.ERROR) {
//			closeConnection();
			String err = response.getErrorMessage();
			throw new Exception(err);
		}
	}

	@Override
	public void logOut(IUserObserver user) throws Exception {
		Request req = new Request();
		req.setType(RequestType.LOGOUT);
		sendRequest(req);
		closeConnection();
	}

	@Override
	public MoveReply move(Move move) throws Exception {
		Request req = new Request();
		req.setType(RequestType.MOVE);
		req.setMove(move);
		req.setGame(move.getGame());
		sendRequest(req);
		Response response = getResponse();
		if (response.getType() == ResponseType.ERROR) {
//			closeConnection();
			String err = response.getErrorMessage();
			throw new Exception(err);
		}
		return response.getMoveReply();
	}

	@Override
	public List<Game> getLeaderboard() throws Exception {
		Request req = new Request();
		req.setType(RequestType.LEADERBOARD);
		sendRequest(req);
		Response response = getResponse();
		if (response.getType() == ResponseType.ERROR) {
//			closeConnection();
			String err = response.getErrorMessage();
			throw new Exception(err);
		}
		return response.getLeaderboard();
	}

	@Override
	public Game startGame(String username) throws Exception {
		Request req = new Request();
		User user = new User();
		user.setUsername(username);
		req.setUser(user);
		req.setType(RequestType.START);
		sendRequest(req);
		Response response = getResponse();
		if (response.getType() == ResponseType.ERROR) {
//			closeConnection();
			String err = response.getErrorMessage();
			throw new Exception(err);
		}
		return response.getGame();
	}

//	@Override
//	public List<ChildDTO> searchChildren(RaceDistance raceDistance, AgeGroup ageGroup) throws Exception {
//		Request req = new Request();
//		req.setSearch(new SearchDTO(raceDistance, ageGroup));
//		req.setType(RequestType.GET_CHILDREN);
//		sendRequest(req);
//		Response response = getResponse();
//		if (response.getType() == ResponseType.ERROR) {
////			closeConnection();
//			String err = response.getErrorMessage();
//			throw new Exception(err);
//		}
//		return response.getChildren();
//	}
//
//	@Override
//	public void signUpChild(String name, Integer age, RaceDistance raceDistance, AgeGroup ageGroup) throws Exception {
//		Request req = new Request();
//		req.setSignup(new SignUpDTO(name, age, raceDistance, ageGroup));
//		req.setType(RequestType.SIGN_UP_CHILD);
//		sendRequest(req);
//		Response response = getResponse();
//		if (response.getType() == ResponseType.ERROR) {
////			closeConnection();
//			String err = response.getErrorMessage();
//			throw new Exception(err);
//		}
//	}
}
