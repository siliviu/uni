package com.example.template.repo;

import com.example.template.domain.Client;
import com.example.template.domain.Flight;

import java.sql.*;
import java.util.ArrayList;
import java.util.Optional;

public class FlightRepo implements Repository<Flight, Long> {
	protected final String url = "jdbc:postgresql://localhost:5432/exam", user = "postgres", password = "piezisa";

	/**
	 * @param id -the id of the entity to be returned
	 *           id must not be null
	 * @return
	 */
	@Override
	public Optional<Flight> get(Long id) {
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT * FROM flights WHERE flightid=?")) {
			statement.setLong(1, id);
			ResultSet resultSet = statement.executeQuery();
			Flight obj = null;
			if (resultSet.next()) {
				obj = new Flight(resultSet.getString("from"),resultSet.getString("to"),resultSet.getTimestamp("departuretime").toLocalDateTime(),resultSet.getTimestamp("landingtime").toLocalDateTime(),resultSet.getInt("seats"));
				obj.setId((long) resultSet.getInt("flightid"));
			}
			return Optional.ofNullable(obj);
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}

	/**
	 * @return
	 */
	@Override
	public ArrayList<Flight> getAll() {
		ArrayList<Flight> l = new ArrayList<>();
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT * FROM flights")) {
			ResultSet resultSet = statement.executeQuery();
			while (resultSet.next()) {
				Flight obj = new Flight(resultSet.getString("from"),resultSet.getString("to"),resultSet.getTimestamp("departuretime").toLocalDateTime(),resultSet.getTimestamp("landingtime").toLocalDateTime(),resultSet.getInt("seats"));
				obj.setId((long) resultSet.getInt("flightid"));
				l.add(obj);
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
	public void add(Flight entity) {
		throw new RuntimeException();
	}
}
