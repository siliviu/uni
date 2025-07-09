package map.lab7.util.pagination;

import java.util.List;

public interface Page<E> {
	Pageable getPageable();

	List<E> getContent();


}

