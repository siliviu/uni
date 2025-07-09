package map.lab7.repository.database;

import map.lab7.domain.User;
import map.lab7.util.pagination.PaginatedRepository;
import map.lab7.util.pagination.Pageable;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class PaginatedUserDBRepository extends UserDBRepository implements PaginatedRepository<Long, User> {
	public int getCount() {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT COUNT(*) FROM users")
		) {
			ResultSet resultSet = statement.executeQuery();
			resultSet.next();
			return resultSet.getInt(1);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	public List<User> getAll(Pageable pageable) {
		List<User> l = new ArrayList<>();
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT * FROM users LIMIT ? OFFSET ?")
		) {
			statement.setInt(1, pageable.getPageSize());
			statement.setInt(2, pageable.getPageNumber() * pageable.getPageSize());
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

}
