package repository;

import domain.Game;

import java.util.Collection;

public interface GameRepository extends Repository<Game, Integer>{
	Collection<Game> getLeaderboard();
}
