package domain;

import jakarta.persistence.*;
import com.fasterxml.jackson.annotation.JsonIgnore;

@Entity
@Table(name = "Move")
public class Move extends Identifiable<Integer> {
	private transient Game game;

	private int y, x;
	private boolean player;

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
	public int getY() {
		return y;
	}

	public void setY(int pos1) {
		this.y = pos1;
	}

	@Column
	public int getX() {
		return x;
	}

	public void setX(int pos2) {
		this.x = pos2;
	}

	@Column
	public boolean isPlayer() {
		return player;
	}

	public void setPlayer(boolean player) {
		this.player = player;
	}
}
