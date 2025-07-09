package repository;

import domain.User;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.hibernate.Session;
import utils.HibernateUtils;

import java.util.Collection;

public class UserHibernateDBRepository implements UserRepository {
	private static final Logger logger = LogManager.getLogger(UserHibernateDBRepository.class.getName());

	@Override
	public User add(User elem) {
		logger.traceEntry("add {}", elem);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			session.persist(elem);
		});
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from User where id=(select max(id) from User)", User.class).uniqueResult();
		}
	}

	@Override
	public void delete(Integer integer) {
		logger.traceEntry("delete, id: {}", integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			User user = session.createQuery("from User where id=?1", User.class).setParameter(1, integer).uniqueResult();
			if (user != null)
				session.remove(user);
		});
	}

	@Override
	public void update(User elem, Integer integer) {
		logger.traceEntry("update {}, id {}", elem, integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			session.merge(elem);
		});
	}

	@Override
	public User getById(Integer integer) {
		logger.traceEntry("get, id {}", integer);
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from User where id=?1", User.class).setParameter(1, integer).uniqueResult();
		}
	}

	@Override
	public Collection<User> getAll() {
		logger.traceEntry("get all");
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from User ", User.class).getResultList();
		}
	}

	@Override
	public User getUserByUsername(String username) {
		logger.traceEntry("get by user {}", username);
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from User where username=?1", User.class).setParameter(1, username).uniqueResult();
		}
	}
}
