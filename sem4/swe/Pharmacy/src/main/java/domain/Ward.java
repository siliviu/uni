package domain;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Table;

@Entity
@Table(name = "Ward")
public class Ward extends Identifiable<Integer>{
	private String name;

	public Ward(){}
	public Ward(String name) {
		this.name = name;
	}

	@Column
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
}
