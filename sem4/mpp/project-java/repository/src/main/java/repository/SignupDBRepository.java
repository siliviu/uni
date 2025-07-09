package repository;

import domain.AgeGroup;
import domain.RaceDistance;
import domain.Signup;
import domain.Child;
import utils.JdbcUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.*;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Properties;

public class SignupDBRepository implements SignupRepository {
	private final JdbcUtils dbUtils;
	private final ChildRepository childrepository;
	private static final Logger logger = LogManager.getLogger(SignupDBRepository.class.getName());

	public SignupDBRepository(Properties props) {
		logger.info("Initializing user repository with properties: {} ", props);
		dbUtils = new JdbcUtils(props);
		childrepository = new ChildDBRepository(props);
	}

	@Override
	public Signup add(Signup elem) {
		logger.traceEntry("add signup {}", elem);
		Connection con = dbUtils.getConnection();
		try (PreparedStatement preparedStatement = con.prepareStatement("INSERT INTO Signup (child_id, age_group, race_distance) values (?,?,?)")) {
			preparedStatement.setInt(1, elem.getChild().getId());
			preparedStatement.setString(2, elem.getAgeGroup().toString());
			preparedStatement.setString(3, elem.getRaceDistance().toString());
			int result = preparedStatement.executeUpdate();
			logger.trace("saved {}", result);
			ResultSet resultSet = con.prepareStatement("SELECT last_insert_rowid()").executeQuery();
			resultSet.next();
			elem.setId(resultSet.getInt(1));
			logger.trace("set id {}", elem.getId());
		} catch (SQLException e) {
			logger.error(e);
			throw new RuntimeException(e);
		}
		logger.traceExit();
		return elem;
	}

	@Override
	public void delete(Integer id) {
		logger.traceEntry("delete signup");
		Connection con = dbUtils.getConnection();
		try (PreparedStatement preparedStatement = con.prepareStatement("DELETE FROM Signup WHERE id=?")) {
			preparedStatement.setInt(1, id);
			int result = preparedStatement.executeUpdate();
			logger.trace("deleted {}", result);
		} catch (SQLException e) {
			logger.error(e);
			throw new RuntimeException(e);
		}
		logger.traceExit();
	}

	@Override
	public void update(Signup elem, Integer id) {
		logger.traceEntry("update signup {}", elem);
		Connection con = dbUtils.getConnection();
		try (PreparedStatement preparedStatement = con.prepareStatement("UPDATE Signup SET child_id=?, age_group=?, race_distance=? WHERE id=?")) {
			preparedStatement.setInt(1, elem.getChild().getId());
			preparedStatement.setString(2, elem.getAgeGroup().toString());
			preparedStatement.setString(3, elem.getRaceDistance().toString());
			preparedStatement.setInt(4, id);
			int result = preparedStatement.executeUpdate();
			logger.trace("saved {}", result);
		} catch (SQLException e) {
			logger.error(e);
			throw new RuntimeException(e);
		}
		logger.traceExit();
	}

	@Override
	public Signup getById(Integer id) {
		logger.traceEntry("get signups {}");
		Connection con = dbUtils.getConnection();
		Signup signup = null;
		try (PreparedStatement preparedStatement = con.prepareStatement("SELECT * FROM Signup WHERE id=?")) {
			preparedStatement.setInt(1, id);
			try (ResultSet resultset = preparedStatement.executeQuery()) {
				if (resultset.next()) {
					Child child = childrepository.getById(resultset.getInt("child_id"));
					AgeGroup ageGroup = AgeGroup.valueOf(resultset.getString("age_group"));
					RaceDistance raceDistance = RaceDistance.valueOf(resultset.getString("race_distance"));
					signup = new Signup(child, ageGroup, raceDistance);
					signup.setId(id);
				} else {
					logger.error("no signup with id");
				}
			}
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
		return signup;
	}

	@Override
	public Collection<Signup> getAll() {
		logger.traceEntry("get signups {}");
		Connection con = dbUtils.getConnection();
		List<Signup> signups = new ArrayList<>();
		try (PreparedStatement preparedStatement = con.prepareStatement("SELECT * FROM Signup")) {
			try (ResultSet resultset = preparedStatement.executeQuery()) {
				while (resultset.next()) {
					Integer id = resultset.getInt("id");
					Child child = childrepository.getById(resultset.getInt("child_id"));
					AgeGroup ageGroup = AgeGroup.valueOf(resultset.getString("age_group"));
					RaceDistance raceDistance = RaceDistance.valueOf(resultset.getString("race_distance"));
					Signup signup = new Signup(child, ageGroup, raceDistance);
					signup.setId(id);
					signups.add(signup);
				}
			}
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
		return signups;
	}

	@Override
	public Collection<Child> getChildrenByRace(AgeGroup ageGroup, RaceDistance raceDistance) {
		logger.traceEntry("get signups {}");
		Connection con = dbUtils.getConnection();
		List<Child> children = new ArrayList<>();
		try (PreparedStatement preparedStatement = con.prepareStatement("SELECT * FROM Signup WHERE age_group=? AND race_distance=?")) {
			preparedStatement.setString(1, ageGroup.toString());
			preparedStatement.setString(2, raceDistance.toString());

			try (ResultSet resultset = preparedStatement.executeQuery()) {
				while (resultset.next()) {
					Child child = childrepository.getById(resultset.getInt("child_id"));
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
	public Integer getChildSignups(Integer id) {
		logger.traceEntry("get no of signups {}");
		Connection con = dbUtils.getConnection();
		try (PreparedStatement preparedStatement = con.prepareStatement("SELECT COUNT(*) FROM Signup WHERE child_id=?")) {
			preparedStatement.setInt(1, id);
			try (ResultSet resultset = preparedStatement.executeQuery()) {
				if (resultset.next()) {
					return resultset.getInt(1);
				}
			}
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
		return 0;
	}
}
