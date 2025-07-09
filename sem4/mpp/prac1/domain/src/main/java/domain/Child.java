package domain;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Table;

import java.io.Serializable;

@Entity
@Table(name = "Child")
public class Child extends Identifiable<Integer> implements Serializable {

	private String name;
	private int age;

	public Child() {};
	public Child(String name, int age) {
		this.name = name;
		this.age = age;
	}

	@Column(name="name")
	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	@Column(name="age")
	public int getAge() {
		return age;
	}

	public void setAge(int age) {
		this.age = age;
	}

	@Override
	public String toString() {
		return "Child{" +
				"name='" + name + '\'' +
				", age=" + age +
				'}';
	}
}
