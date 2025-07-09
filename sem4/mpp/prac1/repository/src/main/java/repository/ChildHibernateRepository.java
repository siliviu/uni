package repository;

import domain.Child;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.hibernate.Session;
import utils.HibernateUtils;

import java.util.Collection;

public class ChildHibernateRepository implements ChildRepository {
	private static final Logger logger = LogManager.getLogger(ChildHibernateRepository.class.getName());

	@Override
	public Child getChildByNameAge(String name, int age) {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Child where name=?1 and age=?2", Child.class).setParameter(1, name).setParameter(2, age).uniqueResult();
		}
	}

	@Override
	public Child add(Child elem) {
		logger.traceEntry("add {}", elem);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			session.persist(elem);
		});
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Child where id=(select max(id) from Child)", Child.class).uniqueResult();
		}
	}

	@Override
	public void delete(Integer integer) {
		logger.traceEntry("delete, id: {}", integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			var entity = session.createQuery("from Child where id=?1", Child.class).setParameter(1, integer).uniqueResult();
			if (entity != null)
				session.remove(entity);
		});
	}

	@Override
	public void update(Child elem, Integer integer) {
		logger.traceEntry("update {}, id {}", elem, integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			elem.setId(integer);
			session.merge(elem);
		});
	}

	@Override
	public Child getById(Integer integer) {
		logger.traceEntry("get, id {}", integer);
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Child where id=?1", Child.class).setParameter(1, integer).uniqueResult();
		}
	}

	@Override
	public Collection<Child> getAll() {
		logger.traceEntry("get all");
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Child ", Child.class).getResultList();
		}
	}
}
