package domain.dto;

import domain.AgeGroup;
import domain.RaceDistance;

public class SearchDTO {
	private RaceDistance raceDistance;
	private AgeGroup ageGroup;

	public SearchDTO(RaceDistance raceDistance, AgeGroup ageGroup) {
		this.raceDistance = raceDistance;
		this.ageGroup = ageGroup;
	}

	public RaceDistance getRaceDistance() {
		return raceDistance;
	}

	public AgeGroup getAgeGroup() {
		return ageGroup;
	}

}
