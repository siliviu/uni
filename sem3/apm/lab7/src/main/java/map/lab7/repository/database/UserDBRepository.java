package map.lab7.repository.database;

import map.lab7.domain.User;
import map.lab7.domain.exceptions.BadValueException;
import map.lab7.repository.Repository;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class UserDBRepository implements Repository<Long, User> {
	 protected final String url = "jdbc:postgresql://localhost:5432/socialnetwork", user = "postgres", password = "piezisa";

	/**
	 * @param id -the id of the entity to be returned
	 *           id must not be null
	 * @return
	 */
	@Override
	public Optional<User> get(Long id) {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT * FROM users WHERE id=?")) {
			statement.setLong(1, id);
			ResultSet resultSet = statement.executeQuery();
			User u = null;
			if (resultSet.next()) {
				u = new User(resultSet.getString("first_name"), resultSet.getString("last_name"));
				u.setId(id);
				PreparedStatement statement2 = connection.prepareStatement("SELECT id2 id FROM friendships WHERE id1 = ? UNION SELECT id1 id FROM friendships WHERE id2 = ?");
				statement2.setLong(1, id);
				statement2.setLong(2, id);
				ResultSet resultSet2 = statement2.executeQuery();
				while (resultSet2.next())
					u.addFriend(resultSet2.getLong("id"));
			}
			return Optional.ofNullable(u);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	/**
	 * @return
	 */
	@Override
	public Iterable<User> getAll() {
		List<User> l = new ArrayList<>();
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECt * FROM users")) {
			ResultSet resultSet = statement.executeQuery();
			while (resultSet.next()) {
				User u = new User(resultSet.getString("first_name"), resultSet.getString("last_name"));
				Long id = resultSet.getLong("id");
				u.setId(id);
				PreparedStatement statement2 = connection.prepareStatement("SELECT id2 id FROM friendships WHERE id1 = ? UNION SELECT id1 id FROM friendships WHERE id2 = ?");
				statement2.setLong(1, id);
				statement2.setLong(2, id);
				ResultSet resultSet2 = statement2.executeQuery();
				while (resultSet2.next())
					u.addFriend(resultSet2.getLong("id"));
				l.add(u);
			}

		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
		return l;
	}

	/**
	 * @param entity entity must be not null
	 * @return
	 */
	@Override
	public Optional<User> add(User entity) {
		if (entity == null)
			throw new BadValueException("entity must be not null");
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("INSERT INTO users (first_name, last_name) VALUES (?,?)")) {
			statement.setString(1, entity.getFirstName());
			statement.setString(2, entity.getLastName());
			int result = statement.executeUpdate();
			return result != 0 ? Optional.empty() : Optional.of(entity);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	/**
	 * @param id id must be not null
	 * @return
	 */
	@Override
	public Optional<User> delete(Long id) {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("DELETE FROM users WHERE id=?")) {
			statement.setLong(1, id);
			var obj = get(id);
			if (obj.isEmpty())
				return Optional.empty();
			statement.executeUpdate();
			return obj;
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	/**
	 * @param entity entity must not be null
	 * @return
	 */
	@Override
	public Optional<User> update(User entity) {

		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("UPDATE users SET first_name=?, last_name=? where id=?")) {
			statement.setString(1, entity.getFirstName());
			statement.setString(2, entity.getLastName());
			statement.setLong(3, entity.getId());
			int result = statement.executeUpdate();
			return result != 0 ? Optional.empty() : Optional.of(entity);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}
}
