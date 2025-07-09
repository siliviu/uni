package map.lab7.domain.validators;

import map.lab7.domain.exceptions.ValidationException;

public interface Validator<T> {
    /**
     * Validates entity
     * @param entity
     * @throws ValidationException
     */
    void validate(T entity) throws ValidationException;
}