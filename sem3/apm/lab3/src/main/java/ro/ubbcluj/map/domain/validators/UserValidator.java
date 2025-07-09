package ro.ubbcluj.map.domain.validators;

import ro.ubbcluj.map.domain.User;
import ro.ubbcluj.map.domain.exceptions.ValidationException;

public class UserValidator implements Validator<User> {
	/**
	 * Validates user entity
 	 * @param entity User
	 * @throws ValidationException
	 */
	@Override
	public void validate(User entity) throws ValidationException {
		if (entity.getFirstName().isEmpty())
			throw new ValidationException("Invalid first name");
		if (entity.getLastName().isEmpty())
			throw new ValidationException("Invalid last name");
	}
}

