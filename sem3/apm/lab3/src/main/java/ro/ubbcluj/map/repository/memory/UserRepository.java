package ro.ubbcluj.map.repository.memory;

import ro.ubbcluj.map.domain.User;
import ro.ubbcluj.map.repository.memory.InMemoryRepository;

import java.util.Optional;

public class UserRepository extends InMemoryRepository<Long, User> {
	private long curId = 1;
	@Override
	public Optional<User> add(User user) {
		user.setId(curId++);
		return super.add(user);
	}
}
