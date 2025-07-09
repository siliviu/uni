package map.lab7.service;

import map.lab7.domain.User;
import map.lab7.domain.validators.UserValidator;
import map.lab7.domain.validators.Validator;
import map.lab7.repository.Repository;
import map.lab7.repository.database.UserDBRepository;
import map.lab7.util.events.UpdateEvent;
import map.lab7.util.Subject;

import java.util.Optional;


public class UserService extends Subject {
	protected final Repository<Long, User> userRepo;
	private static final Validator<User> validator = new UserValidator();
	public UserService() {
		this.userRepo = new UserDBRepository();
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
		broadcast(UpdateEvent.USER);
	}

	/**
	 * Remove user from app based on id
	 *
	 * @param id
	 */
	public void removeUser(Long id) {
		userRepo.delete(id);
		broadcast(UpdateEvent.USER);
	}
	public User getUser(Long id) {
		Optional<User> ans = userRepo.get(id);
		return ans.orElse(null);
	}
	/**
	 * Get a list of all users
	 *
	 * @return
	 */
	public Iterable<User> getUsers() {
		return userRepo.getAll();
	}
	public void updateUser(Long id, String firstName, String lastName) {
		User u = new User(firstName, lastName);
		validator.validate(u);
		u.setId(id);
		userRepo.update(u);
		broadcast(UpdateEvent.USER);
	}


}
