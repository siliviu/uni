package map.lab7.repository.database;

import map.lab7.domain.Friendship;
import map.lab7.domain.Tuple;
import map.lab7.domain.exceptions.BadValueException;
import map.lab7.repository.Repository;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class FriendshipDBRepository implements Repository<Tuple<Long, Long>, Friendship> {
	private final String url = "jdbc:postgresql://localhost:5432/socialnetwork", user = "postgres", password = "piezisa";

	/**
	 * @param id -the id of the entity to be returned
	 *           id must not be null
	 * @return
	 */
	@Override
	public Optional<Friendship> get(Tuple<Long, Long> id) {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT * FROM friendships WHERE id1=? AND id2=?")) {
			statement.setLong(1, id.getLeft());
			statement.setLong(2, id.getRight());
			ResultSet resultSet = statement.executeQuery();
			Friendship f = null;
			if (resultSet.next()) {
				f = new Friendship(resultSet.getTimestamp("date").toLocalDateTime());
				f.setId(new Tuple<>(resultSet.getLong("id1"), resultSet.getLong("id2")));
			}
			return Optional.ofNullable(f);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	/**
	 * @return
	 */
	@Override
	public Iterable<Friendship> getAll() {
		List<Friendship> l = new ArrayList<>();
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT * FROM friendships")) {
			ResultSet resultSet = statement.executeQuery();
			while (resultSet.next()) {
				Friendship f = new Friendship(resultSet.getTimestamp("date").toLocalDateTime());
				f.setId(new Tuple<>(resultSet.getLong("id1"), resultSet.getLong("id2")));
				l.add(f);
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
	public Optional<Friendship> add(Friendship entity) {
		if (entity == null)
			throw new BadValueException("entity must be not null");
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("INSERT INTO friendships (id1,id2,date) VALUES (?,?,?)")) {
			statement.setLong(1, entity.getId().getLeft());
			statement.setLong(2, entity.getId().getRight());
			statement.setTimestamp(3, Timestamp.valueOf(entity.getDate()));
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
	public Optional<Friendship> delete(Tuple<Long, Long> id) {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("DELETE FROM friendships WHERE id1=? AND id2=?")) {
			statement.setLong(1, id.getLeft());
			statement.setLong(2, id.getRight());
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
	public Optional<Friendship> update(Friendship entity) {

		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("UPDATE friendships SET date=? where id1=? and id2=?")) {
			statement.setTimestamp(1, Timestamp.valueOf(entity.getDate()));
			statement.setLong(2, entity.getId().getLeft());
			statement.setLong(3, entity.getId().getRight());
			int result = statement.executeUpdate();
			return result != 0 ? Optional.empty() : Optional.of(entity);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}
}
