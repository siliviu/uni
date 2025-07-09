package map.lab7.util.pagination;

import map.lab7.domain.Entity;
import map.lab7.util.events.UpdateEvent;
import map.lab7.util.Observer;


public class PaginatedService<ID, E extends Entity<ID>> extends Observer {

	int pageSize = 10;
	Page<E> currentPage;
	PaginatedRepository<ID, E> repo;

	@Override
	public void update(UpdateEvent updateEvent) {
		if (updateEvent == UpdateEvent.USER)
			loadPage(getCurrentPageNumber());
	}

	public void loadPage(int pageNumber) {
		Pageable currentPageable = new PageableImplementation(pageNumber, pageSize);
		currentPage = new PageImplementation<>(currentPageable, repo.getAll(currentPageable));
	}

	public PaginatedService(PaginatedRepository<ID, E> repo) {
		this.repo = repo;
		loadPage(0);
	}

	public int getCurrentPageNumber() {
		return currentPage.getPageable().getPageNumber();
	}

	public int getMaximumPageNumber() {
		return (repo.getCount() - 1) / pageSize;
	}

	public void previousPage() {
		if (getCurrentPageNumber() > 0)
			loadPage(getCurrentPageNumber() - 1);
	}

	public void nextPage() {
		if (getCurrentPageNumber() < getMaximumPageNumber())
			loadPage(getCurrentPageNumber() + 1);
	}

	public void changePageSize(int pageSize) {
		this.pageSize = pageSize;
		loadPage(getCurrentPageNumber() * pageSize / this.pageSize);
	}

	public Iterable<E> getAll() {
		return currentPage.getContent();
	}

}
