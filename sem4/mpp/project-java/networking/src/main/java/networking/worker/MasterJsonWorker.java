package networking.worker;

import domain.User;
import domain.dto.SearchDTO;
import domain.dto.SignUpDTO;
import networking.Request;
import networking.RequestType;
import networking.Response;
import networking.ResponseType;
import services.IMasterService;
import services.IUserObserver;

import java.net.Socket;
import javax.jms.*;


public class MasterJsonWorker extends AbstractJsonWorker implements IUserObserver {
	protected final IMasterService service;


	public MasterJsonWorker(IMasterService service, Socket connection) {
		super(connection);
		this.service = service;
	}

	@Override
	protected Response handleRequest(Request request) {
		Response response = null;
		System.out.println(request);
		if (request.getType() == RequestType.LOGIN) {
			System.out.println("Login request ..." + request.getType());
			User user = request.getUser();
			try {
				service.logIn(user.getUsername(), user.getHashedPassword(), this);
				return okResponse;
			} catch (Exception e) {
//				connected = false;
				response = new Response();
				response.setType(ResponseType.ERROR);
				response.setErrorMessage(e.getMessage());
				return response;
			}
		} else if (request.getType() == RequestType.REGISTER) {
			System.out.println("Register request ..." + request.getType());
			User user = request.getUser();
			try {
				service.register(user.getUsername(), user.getHashedPassword());
				return okResponse;
			} catch (Exception e) {
//				connected = false;
				response = new Response();
				response.setType(ResponseType.ERROR);
				response.setErrorMessage(e.getMessage());
				return response;
			}
		} else if (request.getType() == RequestType.GET_CHILDREN) {
			System.out.println("Getting children ..." + request.getType());
			SearchDTO search = request.getSearch();
			try {
				response = new Response();
				response.setType(ResponseType.CHILDREN_LIST);
				response.setChildren(service.searchChildren(search.getRaceDistance(), search.getAgeGroup()));
				return response;
			} catch (Exception e) {
//				connected = false;
				response = new Response();
				response.setType(ResponseType.ERROR);
				response.setErrorMessage(e.getMessage());
				return response;
			}
		} else if (request.getType() == RequestType.SIGN_UP_CHILD) {
			System.out.println("Getting children ..." + request.getType());
			SignUpDTO signUp = request.getSignup();
			try {
				service.signUpChild(signUp.getName(), signUp.getAge(), signUp.getRaceDistance(), signUp.getAgeGroup());
				return okResponse;
			} catch (Exception e) {
//				connected = false;
				response = new Response();
				response.setType(ResponseType.ERROR);
				response.setErrorMessage(e.getMessage());
				return response;
			}
		} else if (request.getType() == RequestType.LOGOUT) {
			connected = false;
			try {
				service.logOut(this);
			} catch (Exception ignored) {
			}
		}
		return response;
	}

	//	@Override
//	public void notifySignup() {
//		Response response = new Response();
//		response.setType(ResponseType.UPDATE_CHILDREN);
//		System.out.println("Received signup notification");
//		try {
//			sendResponse(response);
//		} catch (Exception e) {
//			e.printStackTrace();
//		}
//	}

	@Override
	public void notifySignup() {
	}

}
