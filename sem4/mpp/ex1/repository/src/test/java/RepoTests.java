import domain.*;
import org.junit.jupiter.api.Test;
import repository.*;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

import static org.junit.jupiter.api.Assertions.*;


public class RepoTests {
	@Test
	public void childRepo() {
		Properties props = new Properties();
		try {
			props.load(new FileReader("bd.config"));
		} catch (IOException e) {
			System.out.println("Cannot find bd.config " + e);
		}
		ChildRepository childRepository = new ChildDBRepository(props);
		int initial = childRepository.getAll().size();
		Child c1 = new Child("1", 1);
		c1 = childRepository.add(c1);
		Child c2 = new Child("2", 2);
		c2 = childRepository.add(c2);
		assertEquals(childRepository.getAll().size(), initial + 2);
		assertEquals(childRepository.getById(c1.getId()).getName(), "1");
		assertEquals(childRepository.getById(c2.getId()).getAge(), 2);
		c2.setAge(3);
		childRepository.update(c2, c2.getId());
		assertEquals(childRepository.getById(c2.getId()).getAge(), 3);
		childRepository.delete(c2.getId());
		assertEquals(childRepository.getAll().size(), initial + 1);
		childRepository.delete(c1.getId());
		assertEquals(childRepository.getAll().size(), initial);
	}

	@Test
	public void userRepo() {
		Properties props = new Properties();
		try {
			props.load(new FileReader("bd.config"));
		} catch (IOException e) {
			System.out.println("Cannot find bd.config " + e);
		}
//		UserRepository userRepository = new UserDBRepository(props);
		UserRepository userRepository = new UserHibernateRepository();
		int initial = userRepository.getAll().size();
		User u1 = new User("1", "1");
		u1 = userRepository.add(u1);
		User u2 = new User("2", "2");
		u2 = userRepository.add(u2);
		assertEquals(userRepository.getAll().size(), initial + 2);
		assertEquals(userRepository.getById(u1.getId()).getUsername(), "1");
		assertEquals(userRepository.getById(u2.getId()).getHashedPassword(), "2");
		assertEquals(userRepository.getUserByUsername("1").getHashedPassword(), "1");
		u2.setHashedPassword("3");
		userRepository.update(u2, u2.getId());
		assertEquals(userRepository.getById(u2.getId()).getHashedPassword(), "3");
		userRepository.delete(u2.getId());
		assertEquals(userRepository.getAll().size(), initial + 1);
		userRepository.delete(u1.getId());
		assertEquals(userRepository.getAll().size(), initial);
	}

	@Test
	public void signUpRepo() {
		Properties props = new Properties();
		try {
			props.load(new FileReader("bd.config"));
		} catch (IOException e) {
			System.out.println("Cannot find bd.config " + e);
		}
		ChildRepository childRepository = new ChildDBRepository(props);
		Child c1 = new Child("1", 1);
		c1 = childRepository.add(c1);
		SignupRepository signupRepository = new SignupDBRepository(props);
		int initialChildren = signupRepository.getChildrenByRace(AgeGroup.TWELVE_FIFTEEN, RaceDistance.FIFTEEN_HUNDRED).size();
		int initial = signupRepository.getAll().size();
		Signup s1 = new Signup(c1, AgeGroup.NINE_ELEVEN, RaceDistance.FIFTEEN_HUNDRED);
		s1 = signupRepository.add(s1);
		assertEquals(signupRepository.getAll().size(), initial + 1);
		assertEquals(signupRepository.getById(s1.getId()).getAgeGroup(), AgeGroup.NINE_ELEVEN);
		s1.setAgeGroup(AgeGroup.TWELVE_FIFTEEN);
		signupRepository.update(s1, s1.getId());
		assertEquals(signupRepository.getChildrenByRace(AgeGroup.TWELVE_FIFTEEN, RaceDistance.FIFTEEN_HUNDRED).size(), initialChildren + 1);
		assertEquals(signupRepository.getById(s1.getId()).getAgeGroup(), AgeGroup.TWELVE_FIFTEEN);
		signupRepository.delete(s1.getId());
		assertEquals(signupRepository.getAll().size(), initial);
		childRepository.delete(c1.getId());
	}

}
