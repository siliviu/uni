package repository;

import domain.Medicine;
import org.hibernate.Session;

import java.util.Collection;

public class MedicineHibernateDBRepository implements MedicineRepository {
	@Override
	public Medicine add(Medicine elem) {
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			session.persist(elem);
		});
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Medicine where id=(select max(id) from Medicine)", Medicine.class).uniqueResult();
		}
	}

	@Override
	public void delete(Integer integer) {
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			Medicine entity = session.createQuery("from Medicine where id=?1", Medicine.class).setParameter(1, integer).uniqueResult();
			if (entity != null)
				session.remove(entity);
		});
	}

	@Override
	public void update(Medicine elem, Integer integer) {
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			elem.setId(integer);
			session.merge(elem);
		});
	}

	@Override
	public Medicine getById(Integer integer) {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Medicine where id=?1", Medicine.class).setParameter(1, integer).uniqueResult();
		}
	}

	@Override
	public Collection<Medicine> getAll() {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Medicine ", Medicine.class).getResultList();
		}
	}

	@Override
	public Medicine getMedicineByName(String name) {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Medicine where name=?1", Medicine.class).setParameter(1, name).uniqueResult();
		}
	}
}
