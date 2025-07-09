package domain.dto;

public class ChildDTO {
	private String name;
	private Integer age;
	private Integer signups;

	public ChildDTO(String name, Integer age, Integer signups) {
		this.name = name;
		this.age = age;
		this.signups = signups;
	}

	public Integer getSignups() {
		return signups;
	}

	public void setSignups(Integer signups) {
		this.signups = signups;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public Integer getAge() {
		return age;
	}

	public void setAge(Integer age) {
		this.age = age;
	}
}
