package ro.ubbcluj.map;

import ro.ubbcluj.map.repository.*;
import ro.ubbcluj.map.repository.database.FriendshipDBRepository;
import ro.ubbcluj.map.repository.database.UserDBRepository;
import ro.ubbcluj.map.repository.memory.UserRepository;
import ro.ubbcluj.map.service.Service;
import ro.ubbcluj.map.ui.Console;
import ro.ubbcluj.map.ui.UI;

public class Main {

	public static void main(String[] args) {
		Repository userRepo = new UserDBRepository();
		Repository friendshipRepo = new FriendshipDBRepository();
		Service s = new Service(userRepo, friendshipRepo);

		UI c = new Console(s);
		c.run();
	}
}
