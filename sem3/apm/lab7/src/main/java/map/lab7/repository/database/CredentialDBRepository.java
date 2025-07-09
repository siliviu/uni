package map.lab7.repository.database;

import map.lab7.domain.Credential;
import map.lab7.domain.FriendRequest;
import map.lab7.domain.Message;
import map.lab7.domain.ReplyMessage;
import map.lab7.domain.exceptions.BadValueException;
import map.lab7.repository.Repository;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class CredentialDBRepository implements Repository<String, Credential> {
	private final String url = "jdbc:postgresql://localhost:5432/socialnetwork", user = "postgres", password = "piezisa";

	@Override
	public Optional<Credential> get(String s) {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT * FROM credentials WHERE email=?")) {
			statement.setString(1, s);
			ResultSet resultSet = statement.executeQuery();
			Credential c = null;
			if (resultSet.next())
				c = new Credential(resultSet.getString("email"), resultSet.getString("password"), resultSet.getLong("user_id"));
			return Optional.ofNullable(c);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	@Override
	public Iterable<Credential> getAll() {
		List<Credential> l = new ArrayList<>();
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT * FROM credentials")) {
			ResultSet resultSet = statement.executeQuery();
			while (resultSet.next())
				l.add(new Credential(resultSet.getString("email"), resultSet.getString("password"), resultSet.getLong("user_id")));
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
		return l;
	}

	@Override
	public Optional<Credential> add(Credential entity) {
		if (entity == null)
			throw new BadValueException("entity must be not null");
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("INSERT INTO credentials (email, password, user_id) VALUES (?,?,?)")) {
			statement.setString(1, entity.getEmail());
			statement.setString(2, entity.getPassword());
			statement.setLong(3, entity.getUserId());
			int result = statement.executeUpdate();
			return result != 0 ? Optional.empty() : Optional.of(entity);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	@Override
	public Optional<Credential> delete(String s) {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("DELETE FROM credentials WHERE email=?")) {
			statement.setString(1, s);
			var obj = get(s);
			if (obj.isEmpty())
				return Optional.empty();
			statement.executeUpdate();
			return obj;
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	@Override
	public Optional<Credential> update(Credential entity) {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("UPDATE credentials SET password=?, user_id=? WHERE email=?")) {
			statement.setString(1, entity.getPassword());
			statement.setLong(2, entity.getUserId());
			statement.setString(3, entity.getEmail());
			int result = statement.executeUpdate();
			return result != 0 ? Optional.empty() : Optional.of(entity);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}
}
