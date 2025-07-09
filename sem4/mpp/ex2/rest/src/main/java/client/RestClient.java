package client;

import domain.Game;
import org.springframework.http.HttpRequest;
import org.springframework.http.client.ClientHttpRequestExecution;
import org.springframework.http.client.ClientHttpRequestInterceptor;
import org.springframework.http.client.ClientHttpResponse;

import java.io.IOException;
import java.util.concurrent.Callable;

import static org.springframework.http.MediaType.APPLICATION_JSON;

public class RestClient {
	org.springframework.web.client.RestClient restClient = org.springframework.web.client.RestClient.builder()
			.requestInterceptor(new CustomRestClientInterceptor())
			.build();

	public static final String URL = "http://localhost:8080/app/games";

	private <T> T execute(Callable<T> callable) throws RuntimeException {
		try {
			return callable.call();
		} catch (Exception e) {
			throw new RuntimeException(e);
		}
	}

	public Game getById(Integer id) throws RuntimeException {
		return execute(() -> restClient.get().uri(String.format("%s/%d", URL, id)).retrieve().body(Game.class));
	}

	public void modify(Integer id, String config) throws RuntimeException {
		execute(() -> restClient.put().uri(String.format("%s/%d/configuration", URL, id)).contentType(APPLICATION_JSON).body(config).retrieve().toBodilessEntity());
	}

//	public Game[] get() throws RuntimeException {
//		return execute(() -> restClient.get().uri(URL).retrieve().body(Game[].class));
//	}

//	public Signup getById(Integer id) throws RuntimeException {
//		return execute(() -> restClient.get().uri(String.format("%s/%d", URL, id)).retrieve().body(Signup.class));
//	}
//
//	public Signup create(Signup signup) throws RuntimeException {
//		return execute(() -> restClient.post().uri(URL).contentType(APPLICATION_JSON).body(signup).retrieve().body(Signup.class));
//	}
//
//	public void modify(Signup signup) throws RuntimeException {
//		execute(() -> restClient.put().uri(String.format("%s/%d", URL, signup.getId())).contentType(APPLICATION_JSON).body(signup).retrieve().toBodilessEntity());
//	}
//
//	public void delete(Integer id) throws RuntimeException {
//		execute(() -> restClient.delete().uri(String.format("%s/%d", URL, id)).retrieve().toBodilessEntity());
//	}

	public class CustomRestClientInterceptor
			implements ClientHttpRequestInterceptor {
		@Override
		public ClientHttpResponse intercept(
				HttpRequest request,
				byte[] body,
				ClientHttpRequestExecution execution) throws IOException {
			System.out.println("Sending a " + request.getMethod() + " request to " + request.getURI() + " and body [" + new String(body) + "]");
			ClientHttpResponse response = null;
			try {
				response = execution.execute(request, body);
				System.out.println("Got response code " + response.getStatusCode());
			} catch (IOException ex) {
				System.err.println("Eroare executie " + ex);
			}
			return response;
		}
	}
}
