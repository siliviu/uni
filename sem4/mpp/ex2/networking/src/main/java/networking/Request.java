package networking;


import domain.Game;
import domain.Move;
import domain.User;

public class Request {
	private RequestType type;
	private User user;
	private Game game;
	private Move move;

//    private SearchDTO search;
//    private SignUpDTO signup;

	public Request() {
	}

	public RequestType getType() {
		return type;
	}

	public void setType(RequestType type) {
		this.type = type;
	}

	public User getUser() {
		return user;
	}

	public void setUser(User user) {
		this.user = user;
	}

	public Move getMove() {
		return move;
	}

	public void setMove(Move move) {
		this.move = move;
	}

	public Game getGame() {
		return game;
	}

	public void setGame(Game game) {
		this.game = game;
	}

	@Override
	public String toString() {
		return "Request{" +
				"type=" + type +
				", user=" + user +
				", game=" + game +
				", move=" + move +
				'}';
	}
}
