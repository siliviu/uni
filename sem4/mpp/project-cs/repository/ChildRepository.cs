using project_cs.domain;

namespace project_cs.repo;

public interface IChildRepository : IRepository<Child, int> {
    Child? GetChildByNameAge(String name, int age);
}