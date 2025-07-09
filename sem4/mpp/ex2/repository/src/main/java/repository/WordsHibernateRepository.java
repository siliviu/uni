package repository;

import domain.Word;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.hibernate.Session;
import utils.HibernateUtils;

import java.util.Collection;

public class WordsHibernateRepository implements WordsRepository {
	private static final Logger logger = LogManager.getLogger(WordsHibernateRepository.class.getName());

	@Override
	public Word add(Word elem) {
		logger.traceEntry("add {}", elem);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			session.persist(elem);
		});
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Word where id=(select max(id) from Word)", Word.class).uniqueResult();
		}
	}

	@Override
	public void delete(Integer integer) {
		logger.traceEntry("delete, id: {}", integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			var entity = session.createQuery("from Word where id=?1", Word.class).setParameter(1, integer).uniqueResult();
			if (entity != null)
				session.remove(entity);
		});
	}

	@Override
	public void update(Word elem, Integer integer) {
		logger.traceEntry("update {}, id {}", elem, integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			elem.setId(integer);
			session.merge(elem);
		});
	}

	@Override
	public Word getById(Integer integer) {
		logger.traceEntry("get, id {}", integer);
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Word where id=?1", Word.class).setParameter(1, integer).uniqueResult();
		}
	}

	@Override
	public Collection<Word> getAll() {
		logger.traceEntry("get all");
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Word ", Word.class).getResultList();
		}
	}
}
