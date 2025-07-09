package map.lab7.service;

import map.lab7.domain.*;
import map.lab7.domain.exceptions.BadValueException;
import map.lab7.repository.Repository;
import map.lab7.util.Subject;

import java.time.LocalDateTime;
import java.util.*;
import java.util.stream.Collectors;

public class MasterService  {

	private final UserService userService;

	private final FriendService friendService;

	/**
	 *
	 * @param userService
	 * @param friendService
	 */
	public MasterService(UserService userService, FriendService friendService) {
		this.userService = userService;
		this.friendService = friendService;
	}

	/**
	 * Get the biggest group of users (biggest connected component)*
	 *
	 * @return
	 */
	public Iterable<User> getBiggestGroup() {
		TreeMap<User, Long> components = new TreeMap<>(Comparator.comparing(Entity::getId));
		long curcomp = 0, nrcomp = -1L, size = 0L;
		for (var user : userService.getUsers())
			if (!components.containsKey(user)) {
				long cursize = 0;
				components.put(user, ++curcomp);
				Queue<User> queue = new LinkedList<>();
				queue.add(user);
				while (!queue.isEmpty()) {
					++cursize;
					User current = queue.remove();
					for (var friend : friendService.getFriends(current))
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
		for (var user : userService.getUsers())
			if (!visited.contains(user)) {
				++ans;
				Queue<User> queue = new LinkedList<>();
				queue.add(user);
				visited.add(user);
				while (!queue.isEmpty()) {
					User current = queue.remove();
					for (var friend : friendService.getFriends(current))
						if (!visited.contains(friend)) {
							visited.add(friend);
							queue.add(friend);
						}
				}

			}
		return ans;
	}

	/**
	 * @param id
	 * @return
	 */
	public Iterable<Tuple<User, LocalDateTime>> filterFriendships(Long id, Long month) {
		User u = userService.getUser(id);
		if (u == null)
			throw new BadValueException("User doesn't exist");

		return u.getFriends().stream()
				.map(fid -> new Tuple<>(userService.getUser(fid), friendService.getFriendship(new Tuple<>(Math.min(id, fid), Math.max(id, fid)))))
				.filter(tuple -> tuple.getRight().getDate().getMonthValue() == month)
				.map(tuple -> new Tuple<>(tuple.getLeft(), tuple.getRight().getDate()))
				.collect(Collectors.toList());
	}



}