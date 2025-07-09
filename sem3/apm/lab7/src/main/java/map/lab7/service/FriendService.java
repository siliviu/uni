package map.lab7.service;

import map.lab7.domain.*;
import map.lab7.domain.exceptions.BadValueException;
import map.lab7.domain.exceptions.ValidationException;
import map.lab7.repository.Repository;
import map.lab7.repository.database.FriendRequestDBRepository;
import map.lab7.repository.database.FriendshipDBRepository;
import map.lab7.repository.database.UserDBRepository;
import map.lab7.util.events.UpdateEvent;
import map.lab7.util.Subject;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Optional;
import java.util.stream.Collectors;

public class FriendService extends Subject {

	private final Repository<Tuple<Long, Long>, Friendship> friendshipRepo;
	private final Repository<Tuple<Long, Long>, FriendRequest> friendRequestsRepo;
	private final Repository<Long, User> userRepo;

	public FriendService() {
		this.friendshipRepo = new FriendshipDBRepository();
		this.friendRequestsRepo = new FriendRequestDBRepository();
		this.userRepo = new UserDBRepository();
	}

	/**
	 * Add friendship between two users based on their ids
	 *
	 * @param id1
	 * @param id2
	 * @throws ValidationException
	 */
	public void addFriendship(Long id1, Long id2) throws ValidationException {
		if (id1 == id2)
			throw new BadValueException("User cannot be friends with themselves");
		if (id1 > id2) {
			var aux = id2;
			id2 = id1;
			id1 = aux;
		}
		Optional<User> uu1 = userRepo.get(id1), uu2 = userRepo.get(id2);
		if (uu1.isEmpty() || uu2.isEmpty())
			throw new BadValueException("Invalid users");
		Friendship f = new Friendship(LocalDateTime.now());
		f.setId(new Tuple<>(id1, id2));
		if (friendshipRepo.add(f).isPresent())
			throw new BadValueException("Users are already friends");
		broadcast(UpdateEvent.FRIEND);
	}

	/**
	 * Remove friendship between two users based on ids
	 *
	 * @param id1
	 * @param id2
	 * @throws ValidationException
	 */
	public void removeFriendship(Long id1, Long id2) throws ValidationException {
		if (id1 > id2) {
			var aux = id2;
			id2 = id1;
			id1 = aux;
		}
		Optional<User> uu1 = userRepo.get(id1), uu2 = userRepo.get(id2);
		if (uu1.isEmpty() || uu2.isEmpty())
			throw new BadValueException("Invalid users");
		if (friendshipRepo.delete(new Tuple<>(id1, id2)).isEmpty())
			throw new BadValueException("Users are not friends");
		broadcast(UpdateEvent.FRIEND);
	}


	/**
	 * Get all friends of user
	 *
	 * @param user
	 * @return
	 */
	public Iterable<User> getFriends(User user) {
		Optional<User> uu = userRepo.get(user.getId());
		if (uu.isEmpty())
			throw new BadValueException("User doesn't exist");
		ArrayList<User> ans = uu.get().getFriends().stream().map(userId -> userRepo.get(userId).get()).collect(Collectors.toCollection(ArrayList::new));
		return ans;
	}

	public boolean areFriends(Long id1, Long id2) {
		for (User u : getFriends(userRepo.get(id1).get()))
			if (u.getId().equals(id2))
				return true;
		return false;
	}

	/**
	 * Get a list of all friendships
	 *
	 * @return
	 */
	public Iterable<Friendship> getFriendships() {
		return friendshipRepo.getAll();
	}
	public Friendship getFriendship(Tuple<Long, Long> id) {
		return friendshipRepo.get(id).get();
	}

	public Iterable<FriendRequest> getFriendRequests() {
		return friendRequestsRepo.getAll();
	}

	public void acceptFriendRequest(FriendRequest friendRequest) {
		friendRequest.setState(RequestState.ACCEPTED);
		friendRequestsRepo.update(friendRequest);
		addFriendship(friendRequest.getId().getLeft(), friendRequest.getId().getRight());
		broadcast(UpdateEvent.REQUESTS);
	}

	public void rejectFriendRequest(FriendRequest friendRequest) {
		friendRequest.setState(RequestState.REJECTED);
		friendRequestsRepo.update(friendRequest);
		broadcast(UpdateEvent.REQUESTS);
	}

	public void sendFriendRequest(Long idFrom, Long idTo) {
		FriendRequest friendRequest = new FriendRequest(RequestState.PENDING);
		friendRequest.setId(new Tuple<>(idFrom, idTo));
		if (friendRequestsRepo.add(friendRequest).isPresent())
			throw new BadValueException("A request has been sent before to this user");
		broadcast(UpdateEvent.REQUESTS);
	}
}
