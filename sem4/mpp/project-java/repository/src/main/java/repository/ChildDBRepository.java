package repository;

import domain.Child;
import utils.JdbcUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.*;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Properties;

public class ChildDBRepository implements ChildRepository {
	private final JdbcUtils dbUtils;
	private static final Logger logger = LogManager.getLogger(ChildDBRepository.class.getName());

	public ChildDBRepository(Properties props) {
		logger.info("Initializing child repository with properties: {} ", props);
		dbUtils = new JdbcUtils(props);
	}

	@Override
	public Child add(Child elem) {
		logger.traceEntry("add child {}", elem);
		Connection con = dbUtils.getConnection();
		try (PreparedStatement preparedStatement = con.prepareStatement("INSERT INTO Child (name, age) values (?,?)")) {
			preparedStatement.setString(1, elem.getName());
			preparedStatement.setInt(2, elem.getAge());
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
		logger.traceEntry("delete child");
		Connection con = dbUtils.getConnection();
		try (PreparedStatement preparedStatement = con.prepareStatement("DELETE FROM Child WHERE id=?")) {
			preparedStatement.setInt(1, id);
			int result = preparedStatement.executeUpdate();
			logger.trace("deleted {}", result);
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
	}

	@Override
	public void update(Child elem, Integer id) {
		logger.traceEntry("update child {}", elem);
		Connection con = dbUtils.getConnection();
		try (PreparedStatement preparedStatement = con.prepareStatement("UPDATE Child SET name=?, age=? WHERE id=?")) {
			preparedStatement.setString(1, elem.getName());
			preparedStatement.setInt(2, elem.getAge());
			preparedStatement.setInt(3, id);
			int result = preparedStatement.executeUpdate();
			logger.trace("saved {}", result);
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
	}

	@Override
	public Child getById(Integer id) {
		logger.traceEntry("get children {}");
		Connection con = dbUtils.getConnection();
		Child child = null;
		try (PreparedStatement preparedStatement = con.prepareStatement("SELECT * FROM Child WHERE id=?")) {
			preparedStatement.setInt(1, id);
			try (ResultSet resultset = preparedStatement.executeQuery()) {
				if (resultset.next()) {
					String name = resultset.getString("name");
					int age = resultset.getInt("age");
					child = new Child(name, age);
					child.setId(id);
				} else {
					logger.error("no child with id");
				}
			}
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
		return child;
	}

	@Override
	public Collection<Child> getAll() {
		logger.traceEntry("get children {}");
		Connection con = dbUtils.getConnection();
		List<Child> children = new ArrayList<>();
		try (PreparedStatement preparedStatement = con.prepareStatement("SELECT * FROM Child")) {
			try (ResultSet resultset = preparedStatement.executeQuery()) {
				while (resultset.next()) {
					int id = resultset.getInt("id");
					String name = resultset.getString("name");
					int age = resultset.getInt("age");
					Child child = new Child(name, age);
					child.setId(id);
					children.add(child);
				}
			}
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
		return children;
	}

	@Override
	public Child getChildByNameAge(String name, int age) {
		logger.traceEntry("get if child exists {}");
		Connection con = dbUtils.getConnection();
		Child child = null;
		try (PreparedStatement preparedStatement = con.prepareStatement("SELECT * FROM Child WHERE name=? AND age=?")) {
			preparedStatement.setString(1, name);
			preparedStatement.setInt(2, age);
			try (ResultSet resultset = preparedStatement.executeQuery()) {
				if (resultset.next()) {
					child = new Child(name, age);
					child.setId(resultset.getInt("id"));
				}
			}
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
		return child;
	}
}
