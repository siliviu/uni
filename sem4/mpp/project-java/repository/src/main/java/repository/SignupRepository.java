package repository;

import domain.AgeGroup;
import domain.Child;
import domain.RaceDistance;
import domain.Signup;

import java.util.Collection;

public interface SignupRepository extends Repository<Signup, Integer> {
	Collection<Child> getChildrenByRace(AgeGroup ageGroup, RaceDistance raceDistance);

	Integer getChildSignups(Integer id);
}
