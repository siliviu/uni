package repository;

import domain.Medicine;
import domain.Order;
import domain.OrderItem;
import org.hibernate.Session;

import java.util.Collection;

public class OrderItemHibernateDBRepository implements OrderItemRepository {
	@Override
	public OrderItem add(OrderItem elem) {
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			session.persist(elem);
		});
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from OrderItem where id=(select max(id) from OrderItem)", OrderItem.class).uniqueResult();
		}
	}

	@Override
	public void delete(Integer integer) {
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			OrderItem entity = session.createQuery("from OrderItem where id=?1", OrderItem.class).setParameter(1, integer).uniqueResult();
			if (entity != null)
				session.remove(entity);
		});
	}

	@Override
	public void update(OrderItem elem, Integer integer) {
		HibernateUtils.getSessionFactory().inTransaction(session -> {
			elem.setId(integer);
			session.merge(elem);
		});
	}

	@Override
	public OrderItem getById(Integer integer) {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from OrderItem where id=?1", OrderItem.class).setParameter(1, integer).uniqueResult();
		}
	}

	@Override
	public Collection<OrderItem> getAll() {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from OrderItem ", OrderItem.class).getResultList();
		}
	}

	@Override
	public Collection<OrderItem> getOrderItems(Order order) {
		try (Session session = HibernateUtils.getSessionFactory().openSession()) {
			return session.createQuery("from OrderItem where order.id=?1", OrderItem.class).setParameter(1, order.getId()).getResultList();
		}
	}
}
