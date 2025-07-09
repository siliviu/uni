package repository;

import domain.User;

public interface UserRepository extends Repository<User, Integer> {
	User getUserByUsername(String username);
}
