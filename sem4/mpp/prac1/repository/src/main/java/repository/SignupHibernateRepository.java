package repository;

import domain.AgeGroup;
import domain.Child;
import domain.RaceDistance;
import domain.Signup;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.hibernate.Session;
import utils.HibernateUtils;

import java.util.Collection;

public class SignupHibernateRepository implements SignupRepository {
	private static final Logger logger = LogManager.getLogger(SignupHibernateRepository.class.getName());
	@Override
	public Signup add(Signup elem) {
		logger.traceEntry("add {}", elem);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			session.persist(elem);
		});
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Signup where id=(select max(id) from Signup)", Signup.class).uniqueResult();
		}
	}

	@Override
	public void delete(Integer integer) {
		logger.traceEntry("delete, id: {}", integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			var entity = session.createQuery("from Signup where id=?1", Signup.class).setParameter(1, integer).uniqueResult();
			if (entity != null)
				session.remove(entity);
		});
	}

	@Override
	public void update(Signup elem, Integer integer) {
		logger.traceEntry("update {}, id {}", elem, integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			elem.setId(integer);
			session.merge(elem);
		});
	}

	@Override
	public Signup getById(Integer integer) {
		logger.traceEntry("get, id {}", integer);
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Signup where id=?1", Signup.class).setParameter(1, integer).uniqueResult();
		}
	}

	@Override
	public Collection<Signup> getAll() {
		logger.traceEntry("get all");
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Signup ", Signup.class).getResultList();
		}
	}

	@Override
	public Collection<Child> getChildrenByRace(AgeGroup ageGroup, RaceDistance raceDistance) {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("select child from Signup where ageGroup=?1 and raceDistance=?2", Child.class)
					.setParameter(1, ageGroup)
					.setParameter(2, raceDistance)
					.getResultList();
		}
	}

	@Override
	public Integer getChildSignups(Integer id) {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("select count(*) from Signup where child.id=?1", Long.class).setParameter(1, id).uniqueResult().intValue();
		}
	}
}
