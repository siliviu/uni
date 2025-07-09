package com.example.template.repo;

import com.example.template.domain.Client;
import com.example.template.domain.Ticket;

import java.sql.*;
import java.util.ArrayList;
import java.util.Optional;

public class TicketRepo implements Repository<Ticket, Long> {
	protected final String url = "jdbc:postgresql://localhost:5432/exam", user = "postgres", password = "piezisa";

	/**
	 * @param id -the id of the entity to be returned
	 *           id must not be null
	 * @return
	 */
	@Override
	public Optional<Ticket> get(Long id) {
		throw new RuntimeException();
	}

	/**
	 * @return
	 */
	@Override
	public ArrayList<Ticket> getAll() {
		ArrayList<Ticket> l = new ArrayList<>();
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT * FROM tickets")) {
			ResultSet resultSet = statement.executeQuery();
			while (resultSet.next()) {
				Ticket obj = new Ticket(resultSet.getString("username"), (long) resultSet.getInt("flightid"), resultSet.getTimestamp("purchasetime").toLocalDateTime());
				obj.setId((long) resultSet.getInt("ticketid"));
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
	public void add(Ticket entity) {
		if (entity == null)
			throw new RuntimeException("entity must be not null");
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("INSERT INTO tickets (username, flightid, purchasetime) VALUES (?, ?, ?)")) {
			statement.setString(1, entity.getUsername());
			statement.setInt(2, Math.toIntExact(entity.getFlightId()));
			statement.setTimestamp(3, Timestamp.valueOf(entity.getPurchaseTime()));

			int result = statement.executeUpdate();
		} catch (SQLException e) {
			throw new RuntimeException(e);
		}
	}
}
