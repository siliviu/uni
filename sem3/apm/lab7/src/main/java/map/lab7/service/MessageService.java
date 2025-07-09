package map.lab7.service;

import map.lab7.domain.Message;
import map.lab7.domain.ReplyMessage;
import map.lab7.repository.Repository;
import map.lab7.repository.database.MessageDBRepository;
import map.lab7.util.events.UpdateEvent;
import map.lab7.util.Subject;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class MessageService extends Subject {
	private final Repository<Long, Message> messageRepo;

	public MessageService() {
		this.messageRepo = new MessageDBRepository();
	}

	public Message getMessage(long id) {
		return messageRepo.get(id).get();
	}

	public Iterable<Message> getMessages(Long user, Long user2) {
		List<Message> messages = new ArrayList<>();
		for (Message message : messageRepo.getAll())
			if ((message.getFrom() == user || message.getTo() == user) && (message.getFrom() == user2 || message.getTo() == user2))
				messages.add(message);
		return messages;
	}

	public void sendMessage(Long idfrom, Long idto, String message, Long source) {
		messageRepo.add(source == null ?
				new Message(idfrom, idto, message, LocalDateTime.now()) :
				new ReplyMessage(idfrom,idto, message, LocalDateTime.now(), source));
		broadcast(UpdateEvent.MESSAGE);
	}
}
