package repository;

import domain.Identifiable;

import java.io.Serializable;
import java.util.Collection;

public interface Repository<T extends Identifiable<ID>, ID extends Serializable> {
	T add(T elem);
	void delete(ID id);
	void update(T elem, ID id);
	T getById(ID id);
	Collection<T> getAll();
}

