package services;

import domain.*;

import java.util.List;

public interface IMasterService {
	void register(String username) throws Exception;
	void logIn(String username, IUserObserver user) throws Exception;

	void logOut(IUserObserver user) throws Exception;

	MoveReply move(Move move) throws Exception;

	List<Game> getLeaderboard() throws Exception;

	Game startGame(String user) throws Exception;

//	List<ChildDTO> searchChildren(RaceDistance raceDistance, AgeGroup ageGroup) throws Exception;
//
//	void signUpChild(String name, Integer age, RaceDistance raceDistance, AgeGroup ageGroup) throws Exception;
}
