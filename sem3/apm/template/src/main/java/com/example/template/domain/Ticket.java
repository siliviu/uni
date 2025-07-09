package com.example.template.domain;

import java.time.LocalDateTime;

public class Ticket extends Entity<Long> {
	String username;
	Long flightId;
	LocalDateTime purchaseTime;

	public Ticket(String username, Long flightId, LocalDateTime purchaseTime) {
		this.username = username;
		this.flightId = flightId;
		this.purchaseTime = purchaseTime;
	}

	public String getUsername() {
		return username;
	}

	public void setUsername(String username) {
		this.username = username;
	}

	public Long getFlightId() {
		return flightId;
	}

	public void setFlightId(Long flightId) {
		this.flightId = flightId;
	}

	public LocalDateTime getPurchaseTime() {
		return purchaseTime;
	}

	public void setPurchaseTime(LocalDateTime purchaseTime) {
		this.purchaseTime = purchaseTime;
	}
}
