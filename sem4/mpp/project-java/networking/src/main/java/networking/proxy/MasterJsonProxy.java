package networking.proxy;

import domain.AgeGroup;
import domain.RaceDistance;
import domain.User;
import domain.dto.ChildDTO;
import domain.dto.SearchDTO;
import domain.dto.SignUpDTO;
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
		return response.getType() == ResponseType.UPDATE_CHILDREN;
	}

	protected void handleUpdate(Response response) {
		if (response.getType() == ResponseType.UPDATE_CHILDREN) {
			try {
				user.notifySignup();
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

	@Override
	public void register(String username, String password) throws Exception {
		initializeConnection();
		Request req = new Request();
		req.setUser(new User(username, password));
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
	public void logIn(String username, String password, IUserObserver user) throws Exception {
		initializeConnection();
		Request req = new Request();
		req.setUser(new User(username, password));
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
	public List<ChildDTO> searchChildren(RaceDistance raceDistance, AgeGroup ageGroup) throws Exception {
		Request req = new Request();
		req.setSearch(new SearchDTO(raceDistance, ageGroup));
		req.setType(RequestType.GET_CHILDREN);
		sendRequest(req);
		Response response = getResponse();
		if (response.getType() == ResponseType.ERROR) {
//			closeConnection();
			String err = response.getErrorMessage();
			throw new Exception(err);
		}
		return response.getChildren();
	}

	@Override
	public void signUpChild(String name, Integer age, RaceDistance raceDistance, AgeGroup ageGroup) throws Exception {
		Request req = new Request();
		req.setSignup(new SignUpDTO(name, age, raceDistance, ageGroup));
		req.setType(RequestType.SIGN_UP_CHILD);
		sendRequest(req);
		Response response = getResponse();
		if (response.getType() == ResponseType.ERROR) {
//			closeConnection();
			String err = response.getErrorMessage();
			throw new Exception(err);
		}
	}
}
