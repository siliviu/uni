package ro.ubbcluj.map.repository;

import ro.ubbcluj.map.domain.User;

import java.util.List;

public class UserFileRepository extends AbstractFileRepository<Long, User> {
    private long curId = 1;

    @Override
    public User add(User user) {
        user.setId(curId++);
        return super.add(user);
    }
    public UserFileRepository(String fileName) {
        super(fileName);
    }

    @Override
    public User extractEntity(List<String> attributes) {
        User user = new User(attributes.get(1),attributes.get(2));
        user.setId(Long.parseLong(attributes.get(0)));
        return user;
    }

    @Override
    protected String createEntityAsString(User entity) {
        return entity.getId()+";"+entity.getFirstName()+";"+entity.getLastName();
    }
}
