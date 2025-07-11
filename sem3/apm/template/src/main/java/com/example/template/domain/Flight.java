package com.example.template.domain;

import java.time.LocalDateTime;

public class Flight extends Entity<Long> {
	String from, to;
	LocalDateTime departureTime, landingTime;
	int seats;

	public Flight(String from, String to, LocalDateTime departureTime, LocalDateTime landingTime, int seats) {
		this.from = from;
		this.to = to;
		this.departureTime = departureTime;
		this.landingTime = landingTime;
		this.seats = seats;
	}

	public String getFrom() {
		return from;
	}

	public void setFrom(String from) {
		this.from = from;
	}

	public String getTo() {
		return to;
	}

	public void setTo(String to) {
		this.to = to;
	}

	public LocalDateTime getDepartureTime() {
		return departureTime;
	}

	public void setDepartureTime(LocalDateTime departureTime) {
		this.departureTime = departureTime;
	}

	public LocalDateTime getLandingTime() {
		return landingTime;
	}

	public void setLandingTime(LocalDateTime landingTime) {
		this.landingTime = landingTime;
	}

	public int getSeats() {
		return seats;
	}

	public void setSeats(int seats) {
		this.seats = seats;
	}
}
