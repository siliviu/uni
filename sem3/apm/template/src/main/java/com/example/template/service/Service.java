package com.example.template.service;

import com.example.template.domain.Client;
import com.example.template.domain.Flight;
import com.example.template.domain.Ticket;
import com.example.template.repo.ClientRepo;
import com.example.template.repo.FlightRepo;
import com.example.template.repo.Repository;
import com.example.template.repo.TicketRepo;
import com.example.template.util.Subject;
import com.example.template.util.events.UpdateEvent;

import java.time.LocalDateTime;
import java.util.List;
import java.util.stream.Collectors;

public class Service extends Subject {

	private final Repository<Client, Long> clientRepo;
	private final Repository<Ticket, Long> ticketRepo;
	private final Repository<Flight, Long> flightRepo;

	public Service() {
		this.clientRepo = new ClientRepo();
		this.ticketRepo = new TicketRepo();
		this.flightRepo = new FlightRepo();
	}

	public Client getByUsername(String username) {
		List<Client> list = clientRepo.getAll();
		for (Client c : list)
			if (c.getUsername().equals(username))
				return c;
		throw new RuntimeException("Username does not exist");
	}

	public List<Ticket> getTickets() {
		return ticketRepo.getAll();
	}

	public List<Flight> getFlights() {
		return flightRepo.getAll();
	}


	public List<String> getFrom() {
		return flightRepo.getAll().stream().map(Flight::getFrom).distinct().collect(Collectors.toList());
	}

	public List<String> getTo() {
		return flightRepo.getAll().stream().map(Flight::getTo).distinct().collect(Collectors.toList());
	}

	public void purchaseTicket(Client user, Flight flight) {
		if (getAvailable(flight.getId()) <= 0)
			return;
		ticketRepo.add(new Ticket(user.getUsername(), flight.getId(), LocalDateTime.now()));
		broadcast(UpdateEvent.ALL);
	}

	public int getAvailable(Long flightId) {
		int seats = flightRepo.get(flightId).get().getSeats();
		for (Ticket t : getTickets())
			if (t.getFlightId().equals(flightId))
				seats--;
		return seats;
	}
}
