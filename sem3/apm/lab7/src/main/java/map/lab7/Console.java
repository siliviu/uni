package map.lab7;

import map.lab7.domain.exceptions.ValidationException;
import map.lab7.repository.Repository;
import map.lab7.repository.database.FriendshipDBRepository;
import map.lab7.repository.database.UserDBRepository;
import map.lab7.service.MasterService;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Console implements App {
	private MasterService service;
	private final BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
//
//	private void userMenu() {
//		Runnable printUsers = () -> {
//			System.out.println("""
//					You can add/remove/update users as follows:
//					+ firstName lastName
//					- id
//					? id
//					= id firstName lastName
//					Enter 0 to exit the menu
//					""");
//			System.out.println("The current users are: ");
//			service.getUsers().forEach(user -> System.out.println("Id: " + user.getId().toString() + ", Name:" + user.getFirstName() + " " + user.getLastName()));
//			System.out.println();
//		};
//		printUsers.run();
//		while (true) {
//			try {
//				String s = reader.readLine();
//				char type = s.charAt(0);
//				s = s.substring(1).trim();
//				if (type == '+') {
//					String[] splits = s.split(" ");
//					if (splits.length != 2) throw new ValidationException("Invalid names");
//					service.addUser(splits[0], splits[1]);
//				} else if (type == '-') {
//					Long id = Long.parseLong(s);
//					service.removeUser(id);
//				} else if (type == '?') {
//					Long id = Long.parseLong(s);
//					System.out.println(service.getUser(id));
//				} else if (type == '=') {
//					String[] splits = s.split(" ");
//					if (splits.length != 3)
//						throw new ValidationException("Invalid command");
//					Long id = Long.parseLong(splits[0]);
//					service.updateUser(id, splits[1], splits[2]);
//					System.out.println(service.getUser(id));
//				} else if (type == '0') return;
//				else throw new ValidationException(("Invalid operation"));
//			} catch (Exception e) {
//				System.out.println(e.getMessage());
//			} finally {
//				printUsers.run();
//			}
//		}
//	}
//
//	private void friendMenu() {
//		Runnable printFriendships = () -> {
//			System.out.println("""
//					You can add/remove friendships as follows:
//					+ id1 id2
//					- id1 id1
//					? id
//					Enter 0 to exit the menu
//					""");
//			System.out.println("The current friendships are: ");
//			for (var friendship : service.getFriendships())
//				System.out.println(friendship.getId().getLeft() + " " + friendship.getId().getRight() + " " + friendship.getDate());
//			System.out.println();
//		};
//		printFriendships.run();
//		while (true) {
//			try {
//				String s = reader.readLine();
//				char type = s.charAt(0);
//				s = s.substring(1).trim();
//				if (type == '+') {
//					String[] splits = s.split(" ");
//					if (splits.length != 2) throw new ValidationException("Invalid ids");
//					service.addFriendship(Long.parseLong(splits[0]), Long.parseLong(splits[1]));
//				} else if (type == '-') {
//					String[] splits = s.split(" ");
//					if (splits.length != 2) throw new ValidationException("Invalid ids");
//					service.removeFriendship(Long.parseLong(splits[0]), Long.parseLong(splits[1]));
//				} else if (type == '?') {
//					Long id = Long.parseLong(s);
//					service.getFriends(service.getUser(id)).forEach(System.out::println);
//				} else if (type == '0') return;
//				else throw new ValidationException(("Invalid operation"));
//			} catch (Exception e) {
//				System.out.println(e.getMessage());
//			} finally {
//				printFriendships.run();
//			}
//		}
//	}
//
//	private void communityMenu() {
//		Runnable printCommunity = () -> {
//			System.out.println("""
//					You can view information about your community:
//					1. See number of friend groups
//					2. See biggest friend group
//					3. See frienships of a user in a month
//					Enter 0 to exit the menu
//					""");
//		};
//		printCommunity.run();
//		while (true) {
//			try {
//				String s = reader.readLine();
//				char type = s.charAt(0);
//				s = s.substring(1).trim();
//				if (type == '1') System.out.println(service.getGroups());
//				else if (type == '2') {
//					service.getBiggestGroup().forEach(user -> System.out.println(user.getId().toString() + " " + user.getFirstName() + " " + user.getLastName()));
//				} else if (type == '3') {
//					String[] splits = s.split(" ");
//					Long id = Long.parseLong(splits[0]), month = Long.parseLong(splits[1]);
//					service.filterFriendships(id, month).forEach(tuple -> System.out.println(tuple.getLeft().getFirstName()+" | "+tuple.getLeft().getLastName()+" | "+tuple.getRight().toString()));
//				}else if (type == '0') return;
//				else throw new ValidationException(("Invalid operation"));
//			} catch (Exception e) {
//				System.out.println(e.getMessage());
//			} finally {
//				printCommunity.run();
//			}
//		}
//	}

	/**
	 * Function to run the app
	 */
	@Override
	public void run() {
//		Repository userRepo = new UserDBRepository(), friendshipRepo = new FriendshipDBRepository();
//		service = new MasterService(userRepo, friendshipRepo, null, null);
//		System.out.println("Welcome to the social media app!\n");
//		while (true) {
//			System.out.println("""
//					0. Close
//					1. Manage Users
//					2. Manage Friends
//					3. Manage Communities
//					""");
//			try {
//				int option = Integer.parseInt(reader.readLine());
//				switch (option) {
//					case 0 -> {
//						System.out.println("Goodbye");
//						return;
//					}
//					case 1 -> userMenu();
//					case 2 -> friendMenu();
//					case 3 -> communityMenu();
//					default -> throw new ValidationException("Invalid option");
//				}
//			} catch (Exception e) {
//				System.out.println(e.getMessage());
//			}
//		}
	}
}
