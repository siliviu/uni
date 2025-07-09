using lab14.domain;

namespace lab14.repository;

public class InMemoryRepository<ID, E> : IRepository<ID, E> where E : Entity<ID>
{
    protected IDictionary<ID, E> entities = new Dictionary<ID, E>();

    public IEnumerable<E> FindAll() {
        return entities.Values;
    }
}