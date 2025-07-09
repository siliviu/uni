package domain;

import com.fasterxml.jackson.annotation.JsonIgnore;
import jakarta.persistence.*;

import java.time.LocalDateTime;
import java.util.List;

@Entity
@Table(name = "Game")
public class Game extends Identifiable<Integer> {
	private String user;
	private int points;

	private int start;

	private List<Move> moves;

	private Configuration configuration;


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

	@OneToMany(mappedBy = "game", fetch = FetchType.EAGER)
	public List<Move> getMoves() {
		return moves;
	}

	public void setMoves(List<Move> moves) {
		this.moves = moves;
	}

	@ManyToOne
	@JoinColumn
	public Configuration getConfiguration(){
		return configuration;
	}

	public void setConfiguration(Configuration configuration){
		this.configuration=configuration;
	}

	@Override
	public String toString() {
		return "Game{" +
				"user='" + user + '\'' +
				", points=" + points +
//				", duration=" + duration +
				", moves=" + moves +
				", configuration='" + configuration + '\'' +
				'}';
	}

	@Column
	public int getStart() {
		return start;
	}

	public void setStart(int start) {
		this.start = start;
	}
}
