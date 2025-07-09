package services;

import domain.*;
import javafx.collections.ObservableList;
import repository.MedicineRepository;
import repository.OrderItemRepository;
import repository.OrderRepository;
import utils.Subject;
import utils.UpdateEvent;

import java.time.LocalDateTime;
import java.util.Collection;

public class MasterService extends Subject {
	private final MedicineRepository medicineRepository;
	private final OrderRepository orderRepository;

	private final OrderItemRepository orderItemRepository;

	public MasterService(MedicineRepository medicineRepository, OrderRepository orderRepository, OrderItemRepository orderItemRepository) {
		this.medicineRepository = medicineRepository;
		this.orderRepository = orderRepository;
		this.orderItemRepository = orderItemRepository;
	}

	public Collection<Medicine> getMedicines() {
		return medicineRepository.getAll();
	}

	public Medicine getMedicineByName(String name) {
		return medicineRepository.getMedicineByName(name);
	}

	private boolean updateStock(Medicine medicine, int bought) {
		if (medicine.getStock() == 0)
			return false;
		bought = Math.min(bought, medicine.getStock());
		medicine.setStock(medicine.getStock() - bought);
		medicineRepository.update(medicine, medicine.getId());
		return true;
	}

	public void placeOrder(Collection<OrderItem> items, Ward ward) {
		Order order = new Order(OrderStatus.PENDING, LocalDateTime.now(), ward);
		orderRepository.add(order);
		for (OrderItem orderItem : items) {
			orderItem.setOrder(order);
			if (updateStock(orderItem.getMedicine(), orderItem.getQuantity()))
				orderItemRepository.add(orderItem);
		}
		broadcast(UpdateEvent.PHARMACY);
	}

	public Collection<Order> getPharmacistOrders() {
		return orderRepository.getPendingOrders();
	}

	public Collection<OrderItem> getOrderItems(Order selectedItem) {
		return orderItemRepository.getOrderItems(selectedItem);
	}

	public void completeOrder(Order o) {
		o.setStatus(OrderStatus.COMPLETED);
		orderRepository.update(o, o.getId());
		broadcast(UpdateEvent.WARD);
	}

	public Collection<Order> getWardOrders(Ward ward) {
		return orderRepository.getWardOrders(ward);
	}
}
