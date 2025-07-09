package domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;

import java.util.List;

@Entity
@Table(name = "Game")
public class Game extends Identifiable<Integer> {
	private String user;
	private int points, duration;

	private List<Move> moves;

	private String configuration;


	public Game() {
	}


	@Column
	public String getUser() {
		return user;
	}

	public void setUser(String user) {
		this.user = user;
	}

	@Column
	public int getPoints() {
		return points;
	}

	public void setPoints(int points) {
		this.points = points;
	}

	@Column
	public int getDuration() {
		return duration;
	}

	public void setDuration(int duration) {
		this.duration = duration;
	}

	@Column
	public String getConfiguration() {
		return configuration;
	}

	public void setConfiguration(String configuration) {
		this.configuration = configuration;
	}

	@OneToMany(mappedBy = "game", fetch = FetchType.EAGER)

	public List<Move> getMoves() {
		return moves;
	}

	public void setMoves(List<Move> moves) {
		this.moves = moves;
	}

	@Override
	public String toString() {
		return "Game{" +
				"user='" + user + '\'' +
				", points=" + points +
				", duration=" + duration +
				", moves=" + moves +
				", configuration='" + configuration + '\'' +
				'}';
	}
}
