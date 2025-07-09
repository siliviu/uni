package services;

import domain.*;
import domain.dto.ChildDTO;

import java.util.List;

public interface IMasterService {
	void register(String username, String password) throws Exception;
	void logIn(String username, String password, IUserObserver user) throws Exception;

	void logOut(IUserObserver user) throws Exception;
	List<ChildDTO> searchChildren(RaceDistance raceDistance, AgeGroup ageGroup) throws Exception;

	void signUpChild(String name, Integer age, RaceDistance raceDistance, AgeGroup ageGroup) throws Exception;
}
