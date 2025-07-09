package map.lab7.repository.database;

import map.lab7.domain.*;
import map.lab7.domain.exceptions.BadValueException;
import map.lab7.repository.Repository;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class MessageDBRepository implements Repository<Long, Message> {
	private final String url = "jdbc:postgresql://localhost:5432/socialnetwork", user = "postgres", password = "piezisa";

	/**
	 * @param id -the id of the entity to be returned
	 *           id must not be null
	 * @return
	 */
	@Override
	public Optional<Message> get(Long id) {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT * FROM messages WHERE id=?")) {
			statement.setLong(1, id);
			ResultSet resultSet = statement.executeQuery();
			Message m = null;
			if (resultSet.next()) {
				Long sourceid = resultSet.getLong("sourceid");
				if (sourceid == null)
					m = new Message(resultSet.getLong("idfrom"), resultSet.getLong("idto"), resultSet.getString("message"), resultSet.getTimestamp("date").toLocalDateTime());
				else
					m = new ReplyMessage(resultSet.getLong("idfrom"), resultSet.getLong("idto"), resultSet.getString("message"), resultSet.getTimestamp("date").toLocalDateTime(), sourceid);
				m.setId(resultSet.getLong("id"));
			}
			return Optional.ofNullable(m);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	/**
	 * @return
	 */
	@Override
	public Iterable<Message> getAll() {
		List<Message> l = new ArrayList<>();
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECt * FROM messages")) {
			ResultSet resultSet = statement.executeQuery();
			while (resultSet.next()) {
				Message m;
				Long sourceid = resultSet.getLong("sourceid");
				if (sourceid == 0)
					m = new Message(resultSet.getLong("idfrom"), resultSet.getLong("idto"), resultSet.getString("message"), resultSet.getTimestamp("date").toLocalDateTime());
				else
					m = new ReplyMessage(resultSet.getLong("idfrom"), resultSet.getLong("idto"), resultSet.getString("message"), resultSet.getTimestamp("date").toLocalDateTime(), sourceid);
				m.setId(resultSet.getLong("id"));
				l.add(m);
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
	public Optional<Message> add(Message entity) {
		if (entity == null)
			throw new BadValueException("entity must be not null");
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("INSERT INTO messages (idfrom, idto, message,date,sourceid) VALUES (?,?,?,?,?)")) {
			statement.setLong(1, entity.getFrom());
			statement.setLong(2, entity.getTo());
			statement.setString(3, entity.getMessage());
			statement.setTimestamp(4, Timestamp.valueOf(entity.getDate()));
			if (entity instanceof ReplyMessage)
				statement.setLong(5, ((ReplyMessage) entity).getSourceid());
			else
				statement.setNull(5, Types.BIGINT);

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
	public Optional<Message> delete(Long id) {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("DELETE FROM messages WHERE id=?")) {
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
	public Optional<Message> update(Message entity) {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("UPDATE messages SET idfrom=?, idto=?, message=?,date=? WHERE id=?")) {
			statement.setLong(1, entity.getFrom());
			statement.setLong(2, entity.getTo());
			statement.setString(3, entity.getMessage());
			statement.setTimestamp(4, Timestamp.valueOf(entity.getDate()));
			statement.setLong(5, entity.getId());
			int result = statement.executeUpdate();
			return result != 0 ? Optional.empty() : Optional.of(entity);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}
}
