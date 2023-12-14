package map.lab7.pagination;

import map.lab7.domain.Entity;


public class PaginatedService<ID, E extends Entity<ID>> {

	int pageSize = 10;
	Page<E> currentPage;
	PaginatedRepository<ID, E> repo;

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

	public Iterable<E> getUsers() {
		return currentPage.getContent();
	}

}
