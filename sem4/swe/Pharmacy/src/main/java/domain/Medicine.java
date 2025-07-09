package domain;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Table;

@Entity
@Table(name = "Medicine")
public class Medicine extends Identifiable<Integer>{
	private String name;
	private Integer stock;

	public Medicine() {
	}

	public Medicine(String name, Integer stock) {
		this.name = name;
		this.stock = stock;
	}

	@Column
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	@Column
	public Integer getStock() {
		return stock;
	}

	public void setStock(Integer stock) {
		this.stock = stock;
	}
}
