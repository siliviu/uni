package domain;

import jakarta.persistence.Column;
import jakarta.persistence.Entity;
import jakarta.persistence.Table;

@Entity
@Table(name = "Word")
public class Word extends Identifiable<Integer> {
	private String word;

	public Word() {
	}

	public Word(String word) {
		this.word = word;
	}

	@Column
	public String getWord() {
		return word;
	}

	public void setWord(String word) {
		this.word = word;
	}
}
