import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import javax.xml.transform.Result;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class CarsDBRepository implements CarRepository {

	private final JdbcUtils dbUtils;


	private static final Logger logger = LogManager.getLogger();

	public CarsDBRepository(Properties props) {
		logger.info("Initializing CarsDBRepository with properties: {} ", props);
		dbUtils = new JdbcUtils(props);
	}

	@Override
	public List<Car> findByManufacturer(String manufacturerN) {
		logger.traceEntry("get task {}");
		Connection con = dbUtils.getConnection();
		List<Car> cars = new ArrayList<>();
		try (PreparedStatement preparedStatement = con.prepareStatement("SELECT * FROM Masini WHERE manufacturer=?")) {
			preparedStatement.setString(1, manufacturerN);
			try (ResultSet resultset = preparedStatement.executeQuery()) {
				while (resultset.next()) {
					int id = resultset.getInt("id");
					String manufacturer = resultset.getString("manufacturer");
					String model = resultset.getString("model");
					int year = resultset.getInt("year");
					Car car = new Car(manufacturer, model, year);
					car.setId(id);
					cars.add(car);
				}
			}
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
		return cars;
	}

	@Override
	public List<Car> findBetweenYears(int min, int max) {
		logger.traceEntry("get task {}");
		Connection con = dbUtils.getConnection();
		List<Car> cars = new ArrayList<>();
		try (PreparedStatement preparedStatement = con.prepareStatement("SELECT * FROM Masini WHERE age >= ? AND age <= ?")) {
			preparedStatement.setInt(1, min);
			preparedStatement.setInt(2, max);
			try (ResultSet resultset = preparedStatement.executeQuery()) {
				while (resultset.next()) {
					int id = resultset.getInt("id");
					String manufacturer = resultset.getString("manufacturer");
					String model = resultset.getString("model");
					int year = resultset.getInt("year");
					Car car = new Car(manufacturer, model, year);
					car.setId(id);
					cars.add(car);
				}
			}
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
		return cars;
	}

	@Override
	public void add(Car elem) {
		logger.traceEntry("add task {}", elem);
		Connection con = dbUtils.getConnection();
		try (PreparedStatement preparedStatement = con.prepareStatement("INSERT INTO Masini (manufacturer, model, year) values (?,?,?)")) {
			preparedStatement.setString(1, elem.getManufacturer());
			preparedStatement.setString(2, elem.getModel());
			preparedStatement.setInt(3, elem.getYear());
			int result = preparedStatement.executeUpdate();
			logger.trace("saved {}", result);
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
	}

	@Override
	public void update(Integer integer, Car elem) {
		logger.traceEntry("update task {}", elem);
		Connection con = dbUtils.getConnection();
		try (PreparedStatement preparedStatement = con.prepareStatement("UPDATE Masini SET manufacture=?, model=?, year=?  WHERE id=?")) {
			preparedStatement.setString(1, elem.getManufacturer());
			preparedStatement.setString(2, elem.getModel());
			preparedStatement.setInt(3, elem.getYear());
			preparedStatement.setInt(4, elem.getId());
			int result = preparedStatement.executeUpdate();
			logger.trace("saved {}", result);
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
	}

	@Override
	public Iterable<Car> findAll() {
		logger.traceEntry("get task {}");
		Connection con = dbUtils.getConnection();
		List<Car> cars = new ArrayList<>();
		try (PreparedStatement preparedStatement = con.prepareStatement("SELECT * FROM Masini")) {
			try (ResultSet resultset = preparedStatement.executeQuery()) {
				while (resultset.next()) {
					int id = resultset.getInt("id");
					String manufacturer = resultset.getString("manufacturer");
					String model = resultset.getString("model");
					int year = resultset.getInt("year");
					Car car = new Car(manufacturer, model, year);
					car.setId(id);
					cars.add(car);
				}
			}
		} catch (SQLException e) {
			logger.error(e);
		}
		logger.traceExit();
		return cars;
	}
}
