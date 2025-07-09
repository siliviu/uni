package com.example.template.repo;

import com.example.template.domain.Client;

import java.sql.*;
import java.util.ArrayList;
import java.util.Optional;

public class ClientRepo implements Repository<Client, Long> {
	protected final String url = "jdbc:postgresql://localhost:5432/exam", user = "postgres", password = "piezisa";

	/**
	 * @param id -the id of the entity to be returned
	 *           id must not be null
	 * @return
	 */
	@Override
	public Optional<Client> get(Long id) {
		throw new RuntimeException();
	}

	/**
	 * @return
	 */
	@Override
	public ArrayList<Client> getAll() {
		ArrayList<Client> l = new ArrayList<>();
		try (Connection connection = DriverManager.getConnection(url, user, password);
			 PreparedStatement statement = connection.prepareStatement("SELECT * FROM clients")) {
			ResultSet resultSet = statement.executeQuery();
			while (resultSet.next()) {
				Client obj = new Client(resultSet.getString("username"), resultSet.getString("name"));
				obj.setId((long) resultSet.getInt("clientid"));
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
	public void add(Client entity) {
		throw new RuntimeException();
	}

}
