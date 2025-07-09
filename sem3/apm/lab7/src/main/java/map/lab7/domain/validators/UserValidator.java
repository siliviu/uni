package map.lab7.domain.validators;

import map.lab7.domain.User;
import map.lab7.domain.exceptions.ValidationException;

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

