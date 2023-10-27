package ro.ubbcluj.map.repository;

import ro.ubbcluj.map.domain.Entity;
import ro.ubbcluj.map.domain.Friendship;
import ro.ubbcluj.map.domain.Tuple;
import ro.ubbcluj.map.domain.User;

import java.util.List;

public class FriendshipFileRepository extends AbstractFileRepository<Tuple<Long, Long>, Friendship> {
	public FriendshipFileRepository(String fileName) {
		super(fileName);
	}

	@Override
	public Friendship extractEntity(List<String> attributes) {
		Friendship f = new Friendship();
		f.setId(new Tuple<>(Long.parseLong(attributes.get(0)), Long.parseLong(attributes.get(1))));
		return f;
	}

	@Override
	protected String createEntityAsString(Friendship f) {
		return f.getId().getLeft() + ";" + f.getId().getRight();
	}
}
