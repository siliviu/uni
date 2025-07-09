package server;

import domain.User;
import repository.UserRepository;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import static java.security.MessageDigest.*;

public class LoginService {
	private final UserRepository userRepository;
	public final MessageDigest md;

	{
		try {
			md = getInstance("SHA-512");
		} catch (NoSuchAlgorithmException e) {
			throw new RuntimeException(e);
		}
	}

	private String hash(String salt, String text) {
		String saltedText = salt + text;
		byte[] bytes = md.digest(saltedText.getBytes(StandardCharsets.UTF_8));
		return new String(bytes, StandardCharsets.UTF_8);
	}

	public LoginService(UserRepository userDBRepository) {
		this.userRepository = userDBRepository;
	}

	public synchronized void register(String username, String password) {
		if (userRepository.getUserByUsername(username) != null)
			throw new RuntimeException("User already registered!");
		password = hash("piezisa", password);
		userRepository.add(new User(username, password));
	}

	public synchronized User login(String username, String password) {
		User user = userRepository.getUserByUsername(username);
		if (user == null)
			throw new RuntimeException("No such user exists!");
		password = hash("piezisa", password);
		if (!user.getHashedPassword().equals(password))
			throw new RuntimeException("Wrong password");
		return user;
	}
}
