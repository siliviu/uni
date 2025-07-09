package domain;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Table;

@Entity
@Table(name = "User")
public class User extends Identifiable<Integer> {
	private String username, hashedPassword;

	public User() {
	}

	public User(String username, String hashedPassword) {
		this.username = username;
		this.hashedPassword = hashedPassword;
	}

	@Column(name = "username")
	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	@Column(name = "password")
	public String getHashedPassword() {
		return hashedPassword;
	}

	public void setHashedPassword(String hashedPassword) {
		this.hashedPassword = hashedPassword;
	}

	@Override
	public String toString() {
		return "User{" +
				"username='" + username + '\'' +
				", hashedPassword='" + hashedPassword + '\'' +
				'}';
	}
}
