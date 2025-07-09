package map.lab7.domain;

public class FriendRequest extends Entity<Tuple<Long, Long>> {
	RequestState state;

	public FriendRequest(RequestState state) {
		this.state = state;
	}

	public RequestState getState() {
		return state;
	}

	public void setState(RequestState state) {
		this.state = state;
	}
}
