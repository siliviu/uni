package map.lab7.util.pagination;

import map.lab7.domain.Entity;

import java.util.List;

public interface PaginatedRepository <ID, E extends Entity<ID>> {
	int getCount();
	List<E> getAll(Pageable pageable);
}