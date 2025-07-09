package domain.dto;

import domain.AgeGroup;
import domain.RaceDistance;

public class SignUpDTO {
	private String name;
	private Integer age;
	private RaceDistance raceDistance;
	private AgeGroup ageGroup;

	public SignUpDTO(String name, Integer age, RaceDistance raceDistance, AgeGroup ageGroup) {
		this.name = name;
		this.age = age;
		this.raceDistance = raceDistance;
		this.ageGroup = ageGroup;
	}

	public String getName() {
		return name;
	}

	public Integer getAge() {
		return age;
	}

	public RaceDistance getRaceDistance() {
		return raceDistance;
	}

	public AgeGroup getAgeGroup() {
		return ageGroup;
	}

}
