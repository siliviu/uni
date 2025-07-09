package server;

import domain.*;
import domain.dto.ChildDTO;
import repository.ChildRepository;
import repository.SignupRepository;

import java.util.List;

public class UserService {
	private final ChildRepository childRepository;
	private final SignupRepository signupRepository;

	private static final int MAX_SIGNUPS = 2;

	public UserService(ChildRepository childRepository, SignupRepository signupRepository) {
		this.childRepository = childRepository;
		this.signupRepository = signupRepository;
	}

	public synchronized List<ChildDTO> searchChildren(RaceDistance raceDistance, AgeGroup ageGroup) {
		return signupRepository.getChildrenByRace(ageGroup, raceDistance)
				.stream()
				.map(c -> new ChildDTO(c.getName(), c.getAge(), signupRepository.getChildSignups(c.getId())))
				.toList();
	}

	public synchronized void signUpChild(String name, Integer age, RaceDistance raceDistance, AgeGroup ageGroup) {
		if (ageGroup == null)
			throw new RuntimeException("Invalid age group");
		Child child = childRepository.getChildByNameAge(name, age);
		if (child == null)
			child = childRepository.add(new Child(name, age));
		if (signupRepository.getChildSignups(child.getId()) >= MAX_SIGNUPS)
			throw new RuntimeException("Child has signed up to the maximum of " + MAX_SIGNUPS + " races already.");
		signupRepository.add(new Signup(child, ageGroup, raceDistance));
	}
}
