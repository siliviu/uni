package domain;

import jakarta.persistence.*;

import java.time.LocalDateTime;

@Entity
@Table(name = "Orders")
public class Order extends Identifiable<Integer> {
	private OrderStatus status;
	private LocalDateTime orderDate;
	private Ward ward;

	public Order() {
	}

	public Order(OrderStatus status, LocalDateTime orderDate, Ward ward) {
		this.status = status;
		this.orderDate = orderDate;
		this.ward=ward;
	}

	@Enumerated(EnumType.STRING)
	@Column
	public OrderStatus getStatus() {
		return status;
	}

	public void setStatus(OrderStatus status) {
		this.status = status;
	}

	@Column
	public LocalDateTime getOrderDate() {
		return orderDate;
	}

	public void setOrderDate(LocalDateTime orderDate) {
		this.orderDate = orderDate;
	}

	@ManyToOne
	@JoinColumn(name="ward_id")
	public Ward getWard() {
		return ward;
	}

	public void setWard(Ward ward) {
		this.ward = ward;
	}
}
