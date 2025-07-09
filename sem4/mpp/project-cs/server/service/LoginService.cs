using project_cs.domain;
using project_cs.repo;

namespace project_cs.service;

public class LoginService {
	private readonly IUserRepository _userRepository;

	public LoginService(IUserRepository userRepository) {
		_userRepository = userRepository;
	}

	private string Hash(string salt, string text) {
		var saltedText = salt + text;
		var bytes = System.Text.Encoding.UTF8.GetBytes(saltedText);
		using (var hash = System.Security.Cryptography.SHA512.Create()) {
			var hashedInputBytes = hash.ComputeHash(bytes);
			return System.Text.Encoding.UTF8.GetString(hashedInputBytes);
		}
	}

	public void Register(string username, string password) {
		if (_userRepository.GetUserByUsername(username) != null)
			throw new Exception("User already registered!");
		password = Hash("piezisa", password);
		_userRepository.Add(new User(username, password));
	}

	public User Login(string username, string password) {
		var user = _userRepository.GetUserByUsername(username);
		if (user == null)
			throw new Exception("No such user exists!");
		password = Hash("piezisa", password);
		if (user.hashedPassword != password)
			throw new Exception("Wrong password");
		return user;
	}
}