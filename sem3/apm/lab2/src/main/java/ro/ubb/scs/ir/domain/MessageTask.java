package ro.ubb.scs.ir.domain;

import java.time.DateTimeException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeFormatterBuilder;

public class MessageTask extends Task {
	public static final DateTimeFormatter dtf = DateTimeFormatter.ofPattern("dd/MM/yyyy hh:mm");
	private String message, sender, recipient;
	private LocalDateTime date;

	public MessageTask(String taskID, String desc, String message, String sender, String recipient, LocalDateTime date) {
		super(taskID, desc);
		this.message = message;
		this.sender = sender;
		this.recipient = recipient;
		this.date = date;
	}

	@Override
	public String toString() {
		return super.toString() + " " + message + " " + sender + " " + recipient + " " + dtf.format(date);
	}

	@Override
	public void execute() {
		System.out.println(this.toString() + " executed successfully on " + dtf.format(LocalDateTime.now()));
	}

	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}

	public String getSender() {
		return sender;
	}

	public void setSender(String sender) {
		this.sender = sender;
	}

	public String getRecipient() {
		return recipient;
	}

	public void setRecipient(String recipient) {
		this.recipient = recipient;
	}

	public LocalDateTime getDate() {
		return date;
	}

	public void setDate(LocalDateTime date) {
		this.date = date;
	}
}
