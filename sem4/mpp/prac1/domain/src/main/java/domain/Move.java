package domain;

import jakarta.persistence.*;
import com.fasterxml.jackson.annotation.JsonIgnore;

@Entity
@Table(name = "Move")
public class Move extends Identifiable<Integer> {
	private transient Game game;

	private int pos1, pos2;

	public Move() {
	}

	@ManyToOne
	@JoinColumn
	@JsonIgnore
	public Game getGame() {
		return game;
	}

	public void setGame(Game game) {
		this.game = game;
	}

	@Column
	public int getPos1() {
		return pos1;
	}

	public void setPos1(int pos1) {
		this.pos1 = pos1;
	}

	@Column
	public int getPos2() {
		return pos2;
	}

	public void setPos2(int pos2) {
		this.pos2 = pos2;
	}

}
