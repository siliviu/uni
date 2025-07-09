package repository;

import domain.Move;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.hibernate.Session;
import utils.HibernateUtils;

import java.util.Collection;

public class MoveHibernateRepository implements MoveRepository {
	private static final Logger logger = LogManager.getLogger(MoveHibernateRepository.class.getName());

	@Override
	public Move add(Move elem) {
		logger.traceEntry("add {}", elem);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			session.persist(elem);
		});
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Move where id=(select max(id) from Move)", Move.class).uniqueResult();
		}
	}

	@Override
	public void delete(Integer integer) {
		logger.traceEntry("delete, id: {}", integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			var entity = session.createQuery("from Move where id=?1", Move.class).setParameter(1, integer).uniqueResult();
			if (entity != null)
				session.remove(entity);
		});
	}

	@Override
	public void update(Move elem, Integer integer) {
		logger.traceEntry("update {}, id {}", elem, integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			elem.setId(integer);
			session.merge(elem);
		});
	}

	@Override
	public Move getById(Integer integer) {
		logger.traceEntry("get, id {}", integer);
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Move where id=?1", Move.class).setParameter(1, integer).uniqueResult();
		}
	}

	@Override
	public Collection<Move> getAll() {
		logger.traceEntry("get all");
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Move ", Move.class).getResultList();
		}
	}
}
