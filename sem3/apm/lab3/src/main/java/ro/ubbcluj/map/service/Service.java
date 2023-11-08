package ro.ubbcluj.map.service;

import ro.ubbcluj.map.domain.Entity;
import ro.ubbcluj.map.domain.User;
import ro.ubbcluj.map.domain.exceptions.BadValueException;
import ro.ubbcluj.map.domain.validators.UserValidator;
import ro.ubbcluj.map.domain.exceptions.ValidationException;
import ro.ubbcluj.map.domain.validators.Validator;
import ro.ubbcluj.map.repository.Repository;

import java.util.*;

public class Service {
	private final Repository<Long, User> userRepo;
	//	private final Repository<Tuple<Long, Long>, Friendship> friendshipRepo;
	private static final Validator<User> validator = new UserValidator();

	/**
	 * Constructor initialising repos
	 *
	 * @param repository //	 * @param friendshipRepository
	 */
	public Service(Repository<Long, User> repository) {
		this.userRepo = repository;
//		this.friendshipRepo = friendshipRepository;

//		for (var friendship : friendshipRepo.getAll()) {
//			User u1 = userRepo.get(friendship.getId().getLeft()), u2 = userRepo.get(friendship.getId().getRight());
//			u1.addFriend(u2);
//			u2.addFriend(u1);
//			userRepo.update(u1);
//			userRepo.update(u2);
//		}
	}

	/**
	 * Add user to app (auto generate id, names inputted by user)
	 *
	 * @param firstName
	 * @param lastName
	 */
	public void addUser(String firstName, String lastName) {
		User u = new User(firstName, lastName);
		validator.validate(u);
		userRepo.add(u);
	}

	/**
	 * Remove user from app based on id
	 *
	 * @param id
	 */
	public void removeUser(Long id) {
		userRepo.delete(id);
	}

	/**
	 * Get a list of all users
	 *
	 * @return
	 */

	public User getUser(Long id){
		Optional<User> ans = userRepo.get(id);
		return ans.orElse(null);
	}
	public Iterable<User> getUsers() {
		return userRepo.getAll();
	}

	/**
	 * Add friendship between two users based on their ids
	 *
	 * @param id1
	 * @param id2
	 * @throws ValidationException
	 */
	public void addFriendship(Long id1, Long id2) throws ValidationException {
		if (id1 > id2) {
			var aux = id2;
			id2 = id1;
			id1 = aux;
		}
		Optional<User> uu1 = userRepo.get(id1), uu2 = userRepo.get(id2);
		if (uu1.isEmpty() || uu2.isEmpty())
			throw new BadValueException("Invalid users");
		User u1 = uu1.get(), u2 = uu2.get();
//		Friendship f = new Friendship();
//		f.setId(new Tuple<>(id1, id2));
//		if (friendshipRepo.add(f) != null)
		if (u1.getFriends().contains(u2))
			throw new BadValueException("Users are already friends");
		u1.addFriend(u2);
		u2.addFriend(u1);
		userRepo.update(u1);
		userRepo.update(u2);

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
		User u1 = uu1.get(), u2 = uu2.get();

//		friendshipRepo.delete(new Tuple<>(id1, id2));
		u2.removeFriend(u1);
		u1.removeFriend(u2);
		userRepo.update(u1);
		userRepo.update(u2);
	}
//
//	/**
//	 * Get a list of all friendships
//	 *
//	 * @return
//	 */
//	public Iterable<Friendship> getFriendships() {
//		return friendshipRepo.getAll();
//	}

	/**
	 * Get all friends of user
	 *
	 * @param u
	 * @return
	 */
	public Iterable<User> getFriends(User u) {
		Optional<User> uu = userRepo.get(u.getId());
		if (uu.isEmpty())
			throw new BadValueException("User doesn't exist");
		return uu.get().getFriends();
	}

	public void updateFriend(Long id, String firstName, String lastName) {
		User u=new User(firstName, lastName);
		u.setId(id);
		userRepo.update(u);
	}

	/**
	 * Get the "biggest" group of users (by length of longest path)
	 * (Find the diameter of each connected component using BFS)
	 *
	 * @return
	 */
	public Iterable<User> getBiggestGroup() {
		TreeMap<User, Long> components = new TreeMap<>(Comparator.comparing(Entity::getId));
		long curcomp = 0, nrcomp = -1L, size = 0L;
		for (var user : getUsers())
			if (!components.containsKey(user)) {
				long cursize = 0;
				components.put(user, ++curcomp);
				Queue<User> queue = new LinkedList<>();
				queue.add(user);
				while (!queue.isEmpty()) {
					++cursize;
					User current = queue.remove();
					for (var friend : getFriends(current))
						if (!components.containsKey(friend)) {
							components.put(friend, curcomp);
							queue.add(friend);
						}
				}
				if (cursize > size) {
					size = cursize;
					nrcomp = curcomp;
				}
			}
		ArrayList<User> ans = new ArrayList<>();
		for (var v : components.entrySet())
			if (v.getValue() == nrcomp)
				ans.add(v.getKey());

		return ans;
	}

	/**
	 * Get number of groups (number connected components using BFS)
	 *
	 * @return
	 */
	public long getGroups() {
		long ans = 0;
		TreeSet<User> visited = new TreeSet<>(Comparator.comparing(Entity::getId));
		for (var user : getUsers())
			if (!visited.contains(user)) {
				++ans;
				Queue<User> queue = new LinkedList<>();
				queue.add(user);
				visited.add(user);
				while (!queue.isEmpty()) {
					User current = queue.remove();
					for (var friend : getFriends(current))
						if (!visited.contains(friend)) {
							visited.add(friend);
							queue.add(friend);
						}
				}

			}
		return ans;
	}
}