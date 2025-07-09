package domain;

public class MoveReply {
	String word1, word2;
	boolean ended = false;
	Game game;

	public MoveReply() {
	}

	public MoveReply(String word1, String word2) {
		this.word1 = word1;
		this.word2 = word2;
	}

	public String getWord1() {
		return word1;
	}

	public void setWord1(String word1) {
		this.word1 = word1;
	}

	public String getWord2() {
		return word2;
	}

	public void setWord2(String word2) {
		this.word2 = word2;
	}

	public Game getGame() {
		return game;
	}

	public void setGame(Game game) {
		this.game = game;
	}

	public boolean isEnded() {
		return ended;
	}

	public void setEnded(boolean ended) {
		this.ended = ended;
	}
}
