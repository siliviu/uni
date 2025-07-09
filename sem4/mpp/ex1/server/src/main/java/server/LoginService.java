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

	public LoginService(UserRepository userDBRepository) {
		this.userRepository = userDBRepository;
	}

	public synchronized void register(String username) {
		if (userRepository.getUserByUsername(username) != null)
			throw new RuntimeException("User already registered!");
		userRepository.add(new User(username));
	}

	public synchronized User login(String username) {
		User user = userRepository.getUserByUsername(username);
		if (user == null)
			throw new RuntimeException("No such user exists!");
		return user;
	}
}
