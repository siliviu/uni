package client;

import domain.AgeGroup;
import domain.Child;
import domain.RaceDistance;
import domain.Signup;

public class Main {
	private final static SignupClient client = new SignupClient();

	public static void main(String[] args) {
		Child c = new Child("dorel", 8);
		c.setId(200);
		final Signup s = new Signup(c, AgeGroup.TWELVE_FIFTEEN, RaceDistance.THOUSAND);
		try {
			System.out.println("Adding a new signup " + s);
			Signup ss = client.create(s);
			s.setId(ss.getId());
			System.out.println("Added signup " + s + "(id: " + s.getId() + ")");
			System.out.println("\nPrinting all signups ...");
			show(() -> {
				for (Signup signup : client.get())
					System.out.println(signup + "(id: " + signup.getId() + ")");
			});
		} catch (
				Exception ex) {
			System.out.println("Exception ... " + ex.getMessage());
		}

		System.out.println("\nInfo for signup");
		final Integer id = s.getId();
		show(() -> System.out.println(client.getById(id)));
		s.setRaceDistance(RaceDistance.HUNDRED);
		show(() -> client.modify(s));
		show(() -> System.out.println(client.getById(id)));

		System.out.println("\nDeleting user with id=" + s.getId());

		show(() -> client.delete(id));

		System.out.println("\nPrinting all signups ...");

		show(() -> {
			for (Signup signup : client.get())
				System.out.println(signup + "(id: " + signup.getId() + ")");
		});
	}


	private static void show(Runnable task) {
		try {
			task.run();
		} catch (Exception e) {
			System.out.println("Exception: " + e);
		}
	}
}
