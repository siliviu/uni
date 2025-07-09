package repository;

import domain.Game;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.hibernate.Session;
import utils.HibernateUtils;

import java.util.Collection;

public class GameHibernateRepository implements GameRepository {
	private static final Logger logger = LogManager.getLogger(GameHibernateRepository.class.getName());

	@Override
	public Game add(Game elem) {
		logger.traceEntry("add {}", elem);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			session.persist(elem);
		});
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Game where id=(select max(id) from Game)", Game.class).uniqueResult();
		}
	}

	@Override
	public void delete(Integer integer) {
		logger.traceEntry("delete, id: {}", integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			var entity = session.createQuery("from Game where id=?1", Game.class).setParameter(1, integer).uniqueResult();
			if (entity != null)
				session.remove(entity);
		});
	}

	@Override
	public void update(Game elem, Integer integer) {
		logger.traceEntry("update {}, id {}", elem, integer);
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			elem.setId(integer);
			session.merge(elem);
		});
	}

	@Override
	public Game getById(Integer integer) {
		logger.traceEntry("get, id {}", integer);
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Game where id=?1", Game.class).setParameter(1, integer).uniqueResult();
		}
	}

	@Override
	public Collection<Game> getAll() {
		logger.traceEntry("get all");
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Game ", Game.class).getResultList();
		}
	}

	@Override
	public Collection<Game> getLeaderboard() {
		logger.traceEntry("get leaderboard");
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Game where duration > 0 order by points, duration", Game.class).getResultList();
		}
	}
}
