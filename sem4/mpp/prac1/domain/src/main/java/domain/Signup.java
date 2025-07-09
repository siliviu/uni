package domain;

import jakarta.persistence.*;

import java.io.Serializable;


@Entity
@Table(name = "Signup")
public class Signup extends Identifiable<Integer> implements Serializable{
	private Child child;
	private AgeGroup ageGroup;
	private RaceDistance raceDistance;

	public Signup(){};
	public Signup(Child child, AgeGroup ageGroup, RaceDistance raceDistance) {
		this.child = child;
		this.ageGroup = ageGroup;
		this.raceDistance = raceDistance;
	}

	@ManyToOne
	@JoinColumn(name="child_id")
	public Child getChild() {
		return child;
	}

	public void setChild(Child child) {
		this.child = child;
	}

	@Enumerated(EnumType.STRING)
	@Column(name="age_group")
	public AgeGroup getAgeGroup() {
		return ageGroup;
	}

	public void setAgeGroup(AgeGroup ageGroup) {
		this.ageGroup = ageGroup;
	}

	@Enumerated(EnumType.STRING)
	@Column(name="race_distance")
	public RaceDistance getRaceDistance() {
		return raceDistance;
	}

	public void setRaceDistance(RaceDistance raceDistance) {
		this.raceDistance = raceDistance;
	}

	@Override
	public String toString() {
		return "Signup{" +
				"child=" + child +
				", ageGroup=" + ageGroup +
				", raceDistance=" + raceDistance +
				'}';
	}
}
