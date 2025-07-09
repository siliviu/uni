package domain;

import jakarta.persistence.*;

@Entity
@Table(name = "OrderItem")
public class OrderItem extends Identifiable<Integer> {
	private Order order;
	private Medicine medicine;
	private int quantity;

	public OrderItem() {
	}

	public OrderItem(Order order, Medicine medicine, int quantity) {
		this.order = order;
		this.medicine = medicine;
		this.quantity = quantity;
	}

	@ManyToOne
	@JoinColumn(name = "order_id")
	public Order getOrder() {
		return order;
	}

	public void setOrder(Order order) {
		this.order = order;
	}

	@ManyToOne
	@JoinColumn(name = "medicine_Id")
	public Medicine getMedicine() {
		return medicine;
	}

	public void setMedicine(Medicine medicine) {
		this.medicine = medicine;
	}

	@Column
	public int getQuantity() {
		return quantity;
	}

	public void setQuantity(int quantity) {
		this.quantity = quantity;
	}
}
