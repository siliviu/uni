package domain;

import jakarta.persistence.*;
import com.fasterxml.jackson.annotation.JsonIgnore;

@Entity
@Table(name = "Move")
public class Move extends Identifiable<Integer> {
	private transient Game game;

	private String word;

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


	public String getWord() {
		return word;
	}

	public void setWord(String word) {
		this.word = word;
	}
}
