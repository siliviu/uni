package ro.ubbcluj.map;

import ro.ubbcluj.map.repository.*;
import ro.ubbcluj.map.repository.memory.UserRepository;
import ro.ubbcluj.map.service.Service;
import ro.ubbcluj.map.ui.Console;
import ro.ubbcluj.map.ui.UI;

public class Main {

	public static void main(String[] args) {
		Repository u = new UserRepository();
//		Repository u = new UserDBRepository();
		Service s = new Service(u);
//		s.addUser("a", "b");
//		s.addUser("a", "b");
//		s.addUser("a", "b");
//		s.addUser("a", "b");
//		s.addUser("a", "b");
//		s.addUser("a", "b");
//		s.addUser("a", "b");
//		s.addUser("a", "b");
//		s.addUser("a", "b");
//		s.addUser("a", "b");
//		s.addUser("a", "b");
//		s.addUser("a", "b");
//		s.addUser("a", "b");
//		s.addUser("a", "b");
//		s.addFriendship(1L, 2L);
//		s.addFriendship(2L, 3L);
//		s.addFriendship(3L, 4L);
//		s.addFriendship(2L, 4L);
//		s.addFriendship(5L, 6L);
//		s.addFriendship(7L, 8L);
//		s.addFriendship(8L, 9L);
//		s.addFriendship(13L, 14L);




		UI c = new Console(s);
		c.run();
	}
}
