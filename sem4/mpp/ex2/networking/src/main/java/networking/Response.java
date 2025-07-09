package networking;

import domain.Game;
import domain.MoveReply;

import java.util.List;


public class Response {
	private ResponseType type;
	private String errorMessage;
	private Game game;
	private List<Game> leaderboard;
	private MoveReply moveReply;

	public Response() {
	}

	public ResponseType getType() {
		return type;
	}

	public void setType(ResponseType type) {
		this.type = type;
	}

	public String getErrorMessage() {
		return errorMessage;
	}

	public void setErrorMessage(String errorMessage) {
		this.errorMessage = errorMessage;
	}


	public List<Game> getLeaderboard() {
		return leaderboard;
	}

	public void setLeaderboard(List<Game> leaderboard) {
		this.leaderboard = leaderboard;
	}

	public Game getGame() {
		return game;
	}

	public void setGame(Game game) {
		this.game = game;
	}

	public MoveReply getMoveReply() {
		return moveReply;
	}

	public void setMoveReply(MoveReply moveReply) {
		this.moveReply = moveReply;
	}

	@Override
	public String toString() {
		return "Response{" +
				"type=" + type +
				", errorMessage='" + errorMessage + '\'' +
				", game=" + game +
				", leaderboard=" + leaderboard +
				", moveReply=" + moveReply +
				'}';
	}
}
