package repository;

import domain.Order;
import domain.Ward;
import org.hibernate.Session;

import java.util.Collection;

public class OrderHibernateDBRepository implements OrderRepository {
	@Override
	public Order add(Order elem) {
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			session.persist(elem);
		});
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Order where id=(select max(id) from Order)", Order.class).uniqueResult();
		}
	}

	@Override
	public void delete(Integer integer) {
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			Order entity = session.createQuery("from Order where id=?1", Order.class).setParameter(1, integer).uniqueResult();
			if (entity != null)
				session.remove(entity);
		});
	}

	@Override
	public void update(Order elem, Integer integer) {
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			elem.setId(integer);
			session.merge(elem);
		});
	}

	@Override
	public Order getById(Integer integer) {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Order where id=?1", Order.class).setParameter(1, integer).uniqueResult();
		}
	}

	@Override
	public Collection<Order> getAll() {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Order ", Order.class).getResultList();
		}
	}

	@Override
	public Collection<Order> getPendingOrders() {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Order where status='PENDING' order by orderDate", Order.class).getResultList();
		}
	}

	@Override
	public Collection<Order> getWardOrders(Ward ward) {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from Order where ward.id=?1 order by orderDate", Order.class).setParameter(1, ward.getId()).getResultList();
		}
	}
}
