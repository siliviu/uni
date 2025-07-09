package ro.ubbcluj.map.repository.memory;

import ro.ubbcluj.map.domain.Entity;
import ro.ubbcluj.map.domain.exceptions.BadValueException;
import ro.ubbcluj.map.repository.Repository;

import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
	Map<ID, E> entities;

	public InMemoryRepository() {
		entities = new HashMap<ID, E>();
	}

	@Override
	public Optional<E> get(ID id) {
		if (id == null)
			throw new BadValueException("id must be not null");
		return Optional.ofNullable(entities.get(id));
	}

	@Override
	public Iterable<E> getAll() {
		return entities.values();
	}

	@Override
	public Optional<E> add(E entity) {
		if (entity == null)
			throw new BadValueException("entity must be not null");
		if (entities.get(entity.getId()) != null)
			return Optional.ofNullable(entity);
		else
			entities.put(entity.getId(), entity);
		return Optional.empty();
	}

	@Override
	public Optional<E> delete(ID id) {
		if (!entities.containsKey(id))
			throw new BadValueException("Repo does not contain entity with given id");
		return Optional.ofNullable(entities.remove(id));
	}

	@Override
	public Optional<E> update(E entity) {
		if (entity == null)
			throw new BadValueException("entity must be not null!");

		entities.put(entity.getId(), entity);

		if (entities.get(entity.getId()) != null) {
			entities.put(entity.getId(), entity);
			return Optional.empty();
		}
		return Optional.of(entity);

	}
}
