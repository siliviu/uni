package map.lab7.domain;

import java.time.LocalDateTime;
import java.util.ArrayList;

public class Message extends Entity<Long> {
	Long from;

	Long to;

	String message;
	LocalDateTime date;


	public Message(Long from, Long to, String message, LocalDateTime date) {
		this.from = from;
		this.to = to;
		this.message = message;
		this.date = date;
	}

	public Long getFrom() {
		return from;
	}

	public Long getTo() {
		return to;
	}

	public String getMessage() {
		return message;
	}

	public LocalDateTime getDate() {
		return date;
	}
}