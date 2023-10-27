package ro.ubbcluj.map.repository;

import ro.ubbcluj.map.domain.Entity;
import ro.ubbcluj.map.domain.BadValueException;

import java.util.HashMap;
import java.util.Map;

public class InMemoryRepository<ID, E extends Entity<ID>> implements Repository<ID, E> {
	Map<ID, E> entities;

	public InMemoryRepository() {
		entities = new HashMap<ID, E>();
	}

	@Override
	public E get(ID id) {
		if (id == null)
			throw new BadValueException("id must be not null");
		return entities.get(id);
	}

	@Override
	public Iterable<E> getAll() {
		return entities.values();
	}

	@Override
	public E add(E entity) {
		if (entity == null)
			throw new BadValueException("entity must be not null");
		if (entities.get(entity.getId()) != null)
			return entity;
		else
			entities.put(entity.getId(), entity);
		return null;
	}

	@Override
	public E delete(ID id) {
		if (!entities.containsKey(id))
			throw new BadValueException("Repo does not contain entity with given id");
		return entities.remove(id);
	}

	@Override
	public E update(E entity) {
		if (entity == null)
			throw new BadValueException("entity must be not null!");

		entities.put(entity.getId(), entity);

		if (entities.get(entity.getId()) != null) {
			entities.put(entity.getId(), entity);
			return null;
		}
		return entity;

	}
}
