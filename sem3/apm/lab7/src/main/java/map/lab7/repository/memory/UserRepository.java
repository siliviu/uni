package map.lab7.repository.memory;

import map.lab7.domain.User;

import java.util.Optional;

public class UserRepository extends InMemoryRepository<Long, User> {
	private long curId = 1;
	@Override
	public Optional<User> add(User user) {
		user.setId(curId++);
		return super.add(user);
	}
}
