package repository;

import domain.Order;
import domain.Ward;

import java.util.Collection;

public interface OrderRepository extends Repository<Order, Integer> {
	Collection<Order> getPendingOrders();

	Collection<Order> getWardOrders(Ward ward);
}
