package map.lab7.domain;

public class Credential extends Entity<String> {
	String email;

	String password;
	Long userId;

	public Credential(String email, String password, long userId) {
		this.email = email;
		this.password = password;
		this.userId = userId;
	}

	public String getEmail() {
		return email;
	}

	public String getPassword() {
		return password;
	}

	public Long getUserId() {
		return userId;
	}
}
