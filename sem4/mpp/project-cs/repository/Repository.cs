using project_cs.domain;

namespace project_cs.repo;

public interface IRepository<T, TId> where T : Identifiable<TId> {
    T Add(T elem);
    void Delete(TId id);
    void Update(T elem, TId id);
    T? GetById(TId id);
    ICollection<T> GetAll();
}