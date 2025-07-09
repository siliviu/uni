using lab14.domain;

namespace lab14.repository;
public interface Reader<T> {
    T Parse(string s);
}
public class InFileRepository<ID, E> : InMemoryRepository<ID, E> where E : Entity<ID> {
    protected string fileName;
    private Reader<E> reader;

    public InFileRepository(string fileName, Reader<E> reader) {
        this.fileName = fileName;
        this.reader = reader;
        entities = LoadFromFile().ToDictionary(e => e.id);
    }
    protected List<E> LoadFromFile() {
        List<E> list = new List<E>();
        using (StreamReader sr = new StreamReader(fileName)) {
            string s;
            while ((s = sr.ReadLine()) != null) {
                E entity = reader.Parse(s);
                list.Add(entity);
            }
        }
        return list;
    }
}