using lab14.domain;

namespace lab14.repository;

public interface IRepository<ID, E> where E : Entity<ID> {
    IEnumerable<E> FindAll();
}