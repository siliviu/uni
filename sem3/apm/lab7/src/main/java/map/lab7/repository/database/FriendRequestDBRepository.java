package map.lab7.repository.database;

import map.lab7.domain.FriendRequest;
import map.lab7.domain.Friendship;
import map.lab7.domain.RequestState;
import map.lab7.domain.Tuple;
import map.lab7.domain.exceptions.BadValueException;
import map.lab7.repository.Repository;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class FriendRequestDBRepository implements Repository<Tuple<Long, Long>, FriendRequest> {
	private final String url = "jdbc:postgresql://localhost:5432/socialnetwork", user = "postgres", password = "piezisa";

	/**
	 * @param id -the id of the entity to be returned
	 *           id must not be null
	 * @return
	 */

	@Override
	public Optional<FriendRequest> get(Tuple<Long, Long> id) {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT * FROM friend_requests WHERE id1=? AND id2=?")) {
			statement.setLong(1, id.getLeft());
			statement.setLong(2, id.getRight());
			ResultSet resultSet = statement.executeQuery();
			FriendRequest f = null;
			if (resultSet.next()) {
				f = new FriendRequest(RequestState.valueOf(resultSet.getString("state")));
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
	public Iterable<FriendRequest> getAll() {
		List<FriendRequest> l = new ArrayList<>();
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT * FROM friend_requests")) {
			ResultSet resultSet = statement.executeQuery();
			while (resultSet.next()) {
				FriendRequest f = new FriendRequest(RequestState.valueOf(resultSet.getString("state")));
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
	public Optional<FriendRequest> add(FriendRequest entity) {
		if (entity == null)
			throw new BadValueException("entity must be not null");
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("INSERT INTO friend_requests (id1,id2) VALUES (?,?)")) {
			statement.setLong(1, entity.getId().getLeft());
			statement.setLong(2, entity.getId().getRight());
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
	public Optional<FriendRequest> delete(Tuple<Long, Long> id) {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("DELETE FROM friend_requests WHERE id1=? AND id2=?")) {
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
	public Optional<FriendRequest> update(FriendRequest entity) {

		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("UPDATE friend_requests SET state=?::state where id1=? and id2=?")) {
			statement.setString(1, entity.getState().toString());
			statement.setLong(2, entity.getId().getLeft());
			statement.setLong(3, entity.getId().getRight());
			int result = statement.executeUpdate();
			return result != 0 ? Optional.empty() : Optional.of(entity);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}
}
