using project_cs.domain;

namespace project_cs.repo;

public interface IUserRepository : IRepository<User, int> {
    public User? GetUserByUsername(String username);
}