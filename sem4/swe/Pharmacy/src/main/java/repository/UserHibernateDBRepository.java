package repository;

import domain.User;
import org.hibernate.Session;

import java.util.Collection;

public class UserHibernateDBRepository implements UserRepository {
	@Override
	public User add(User elem) {
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			session.persist(elem);
		});
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from User where id=(select max(id) from User)", User.class).uniqueResult();
		}
	}

	@Override
	public void delete(Integer integer) {
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			User user = session.createQuery("from User where id=?1", User.class).setParameter(1, integer).uniqueResult();
			if (user != null)
				session.remove(user);
		});
	}

	@Override
	public void update(User elem, Integer integer) {
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			elem.setId(integer);
			session.merge(elem);
		});
	}

	@Override
	public User getById(Integer integer) {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from User where id=?1", User.class).setParameter(1, integer).uniqueResult();
		}
	}

	@Override
	public Collection<User> getAll() {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from User ", User.class).getResultList();
		}
	}

	@Override
	public User getUserByUsername(String username) {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from User where username=?1", User.class).setParameter(1, username).uniqueResult();
		}
	}
}
