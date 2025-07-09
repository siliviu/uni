package repository;

import domain.User;
import utils.JdbcUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.*;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Properties;


public class UserDBRepository implements UserRepository {
	private final JdbcUtils dbUtils;
	private static final Logger logger = LogManager.getLogger(UserDBRepository.class.getName());

	public UserDBRepository(Properties props) {
		logger.info("Initializing user repository with properties: {} ", props);
		dbUtils = new JdbcUtils(props);
	}

	@Override
	public User add(User elem) {
		logger.traceEntry("add user {}", elem);
		Connection con = dbUtils.getConnection();
		try (PreparedStatement preparedStatement = con.prepareStatement("INSERT INTO User (username, password) values (?,?)")) {
			preparedStatement.setString(1, elem.getUsername());
			preparedStatement.setString(2, elem.getHashedPassword());
			int result = preparedStatement.executeUpdate();
			logger.trace("saved {}", result);
			ResultSet resultSet = con.prepareStatement("SELECT last_insert_rowid()").executeQuery();
			resultSet.next();
			elem.setId(resultSet.getInt(1));
			logger.trace("set id {}", elem.getId());
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
		return elem;
	}

	@Override
	public void delete(Integer id) {
		logger.traceEntry("delete user");
		Connection con = dbUtils.getConnection();
		try (PreparedStatement preparedStatement = con.prepareStatement("DELETE FROM User WHERE id=?")) {
			preparedStatement.setInt(1, id);
			int result = preparedStatement.executeUpdate();
			logger.trace("deleted {}", result);
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
	}

	@Override
	public void update(User elem, Integer id) {
		logger.traceEntry("update user {}", elem);
		Connection con = dbUtils.getConnection();
		try (PreparedStatement preparedStatement = con.prepareStatement("UPDATE User SET username=?, password=? WHERE id=?")) {
			preparedStatement.setString(1, elem.getUsername());
			preparedStatement.setString(2, elem.getHashedPassword());
			preparedStatement.setInt(3, id);
			int result = preparedStatement.executeUpdate();
			logger.trace("saved {}", result);
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
	}

	@Override
	public User getById(Integer id) {
		logger.traceEntry("get user {}");
		Connection con = dbUtils.getConnection();
		User user = null;
		try (PreparedStatement preparedStatement = con.prepareStatement("SELECT * FROM User WHERE id=?")) {
			preparedStatement.setInt(1, id);
			try (ResultSet resultset = preparedStatement.executeQuery()) {
				if (resultset.next()) {
					String username = resultset.getString("username");
					String password = resultset.getString("password");
					user = new User(username, password);
					user.setId(id);
				} else {
					logger.error("no child with id");
				}
			}
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
		return user;
	}

	@Override
	public Collection<User> getAll() {
		logger.traceEntry("get users {}");
		Connection con = dbUtils.getConnection();
		List<User> users = new ArrayList<>();
		try (PreparedStatement preparedStatement = con.prepareStatement("SELECT * FROM User")) {
			try (ResultSet resultset = preparedStatement.executeQuery()) {
				while (resultset.next()) {
					int id = resultset.getInt("id");
					String username = resultset.getString("username");
					String password = resultset.getString("password");
					User user = new User(username, password);
					user.setId(id);
					users.add(user);
				}
			}
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
		return users;
	}

	@Override
	public User getUserByUsername(String username) {
		logger.traceEntry("get user by username {}");
		Connection con = dbUtils.getConnection();
		User user = null;
		try (PreparedStatement preparedStatement = con.prepareStatement("SELECT * FROM User WHERE username=?")) {
			preparedStatement.setString(1, username);
			try (ResultSet resultset = preparedStatement.executeQuery()) {
				if (resultset.next()) {
					String password = resultset.getString("password");
					int id = resultset.getInt("id");
					user = new User(username, password);
					user.setId(id);
				} else {
					logger.error("no user with id");
				}
			}
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
		return user;
	}
}
