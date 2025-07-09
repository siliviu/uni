package repository;

import domain.Configuration;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.hibernate.Session;
import utils.HibernateUtils;

import java.util.Collection;

public class ConfigurationHibernateRepo implements ConfigurationRepo {
	private static final Logger logger = LogManager.getLogger(ConfigurationHibernateRepo.class.getName());

	@Override
	public Configuration add(Configuration elem) {
		logger.traceEntry("add {}", elem);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			session.persist(elem);
		});
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Configuration where id=(select max(id) from Configuration)", Configuration.class).uniqueResult();
		}
	}

	@Override
	public void delete(Integer integer) {
		logger.traceEntry("delete, id: {}", integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			var entity = session.createQuery("from Configuration where id=?1", Configuration.class).setParameter(1, integer).uniqueResult();
			if (entity != null)
				session.remove(entity);
		});
	}

	@Override
	public void update(Configuration elem, Integer integer) {
		logger.traceEntry("update {}, id {}", elem, integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			elem.setId(integer);
			session.merge(elem);
		});
	}

	@Override
	public Configuration getById(Integer integer) {
		logger.traceEntry("get, id {}", integer);
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Configuration where id=?1", Configuration.class).setParameter(1, integer).uniqueResult();
		}
	}

	@Override
	public Collection<Configuration> getAll() {
		logger.traceEntry("get all");
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Configuration ", Configuration.class).getResultList();
		}
	}
}
