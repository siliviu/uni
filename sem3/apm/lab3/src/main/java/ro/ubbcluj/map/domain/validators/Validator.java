package ro.ubbcluj.map.domain.validators;

import ro.ubbcluj.map.domain.exceptions.ValidationException;

public interface Validator<T> {
    /**
     * Validates entity
     * @param entity
     * @throws ValidationException
     */
    void validate(T entity) throws ValidationException;
}