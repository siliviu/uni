package map.lab7.service;

import map.lab7.domain.Credential;
import map.lab7.domain.User;
import map.lab7.domain.exceptions.BadValueException;
import map.lab7.repository.Repository;
import map.lab7.repository.database.CredentialDBRepository;

import java.nio.charset.StandardCharsets;
import java.security.*;
import java.util.Arrays;
import java.util.Optional;

import static java.security.MessageDigest.*;

public class LoginService {
	private final Repository<String, Credential> credentialRepo;
	private final UserService userService;
	public final MessageDigest md = getInstance("SHA-512");


	public LoginService(UserService userService) throws NoSuchAlgorithmException {
		this.credentialRepo = new CredentialDBRepository();
		this.userService = userService;
	}

	public User getUser(String email) {
		return userService.getUser(credentialRepo.get(email).get().getUserId());
	}

	public String hash(String salt, String text) {
		md.update(salt.getBytes());
		return Arrays.toString(md.digest(text.getBytes(StandardCharsets.UTF_8)));
	}

	public void login(String email, String password) {
		Optional<Credential> c = credentialRepo.get(email);
		if (c.isEmpty())
			throw new BadValueException("No user with given email exists");
		if (!c.get().getPassword().equals(hash(email + getUser(email).getId(), password)))
			throw new BadValueException("Wrong password");
	}

	public void register(String email, String password, String firstname, String lastname) {
		if (credentialRepo.get(email).isPresent())
			throw new BadValueException("User already exists with given email");
		userService.addUser(firstname, lastname);
		Iterable<User> l = userService.getUsers();
		User u = null;
		for (User user : l)
			u = user;
		assert u != null;
		credentialRepo.add(new Credential(email, hash(email + u.getId(), password), u.getId()));
	}

}
