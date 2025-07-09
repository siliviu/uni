package domain;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Table;

@Entity
@Table(name = "User")
public class User extends Identifiable<Integer> {
	private String username;

	public User() {
	}

	public User(String username) {
		this.username = username;
	}

	@Column(name = "username")
	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	@Override
	public String toString() {
		return "User{" +
				"username='" + username + '\'' +
				'}';
	}
}
