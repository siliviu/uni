package ro.ubbcluj.map.repository.file;

import ro.ubbcluj.map.domain.User;
import ro.ubbcluj.map.repository.file.AbstractFileRepository;

import java.util.List;
import java.util.Optional;

public class UserFileRepository extends AbstractFileRepository<Long, User> {
    private long curId = 1;

    /**
     *
     * @param user
     *         entity must be not null
     * @return
     */
    @Override
    public Optional<User> add(User user) {
        user.setId(curId++);
        return super.add(user);
    }

    /**
     *
     * @param fileName
     */
    public UserFileRepository(String fileName) {
        super(fileName);
    }

    /**
     *
     * @param attributes
     * @return
     */
    @Override
    public User extractEntity(List<String> attributes) {
        User user = new User(attributes.get(1),attributes.get(2));
        user.setId(Long.parseLong(attributes.get(0)));
        return user;
    }

    /**
     *
     * @param entity
     * @return
     */
    @Override
    protected String createEntityAsString(User entity) {
        return entity.getId()+";"+entity.getFirstName()+";"+entity.getLastName();
    }
}
