package repository;

import domain.Order;
import domain.OrderItem;

import java.util.Collection;

public interface OrderItemRepository extends Repository<OrderItem, Integer> {
	Collection<OrderItem> getOrderItems(Order order);
}
