package map.lab7.pagination;

import java.util.List;

public interface Page<E> {
	Pageable getPageable();

	List<E> getContent();


}

