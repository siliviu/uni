package map.lab7.service;

import map.lab7.domain.*;

import java.util.ArrayList;
import java.util.stream.Collectors;
import java.util.stream.StreamSupport;

public class ClientService {
	private final MessageService messageService;
	private final UserService userService;
	private final FriendService friendService;
	User user;

	public ClientService(MessageService messageService, UserService userService, FriendService friendService, User user) {
		this.messageService = messageService;
		this.userService = userService;
		this.friendService = friendService;
		this.user = user;
	}

	public User getUser() {
		return user;
	}


	public Iterable<User> getOtherUsers() {
		return StreamSupport.stream(userService.getUsers().spliterator(), false).filter(u -> u.getId() != user.getId()).toList();
	}

	public Iterable<User> getFriends() {
		return friendService.getFriends(user);
	}

	public ArrayList<FriendRequest> getFriendRequests(User user) {
		return StreamSupport.stream(friendService.getFriendRequests().spliterator(), false)
				.filter(req -> req.getId().getRight() == user.getId() && req.getState() == RequestState.PENDING)
				.collect(Collectors.toCollection(ArrayList::new));
	}

	public void sendMessage(Long idTo, String message, Long source) {
		messageService.sendMessage(user.getId(), idTo, message, source);
	}

	public Iterable<Message> getUserMessages(Long otherUser) {
		return messageService.getMessages(user.getId(), otherUser);
	}


}
