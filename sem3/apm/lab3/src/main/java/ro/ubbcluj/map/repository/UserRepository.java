package ro.ubbcluj.map.repository;

import ro.ubbcluj.map.domain.User;

public class UserRepository extends InMemoryRepository<Long, User> {
	private long curId = 1;
	@Override
	public User add(User user) {
		user.setId(curId++);
		return super.add(user);
	}
}
