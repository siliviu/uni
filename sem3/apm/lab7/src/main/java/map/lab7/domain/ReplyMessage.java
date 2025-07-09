package map.lab7.domain;

import java.time.LocalDateTime;

public class ReplyMessage extends Message {
	Long sourceid;
	public Long getSourceid() {
		return sourceid;
	}


	public ReplyMessage(Long from, Long to, String message, LocalDateTime date, Long sourceid) {
		super(from, to, message, date);
		this.sourceid = sourceid;
	}
}
