namespace project_cs {
	// internal static class Tests {
	// 	public static void TestAll() {
	// 		//TestRepos();
	// 	}
	//
	// 	private static void TestRepos() {
	// 		IChildRepository childRepository = new ChildDbRepository(Program.props);
	// 		int initial = childRepository.GetAll().Count();
	// 		Child c = new Child("2", 3);
	// 		Child c2 = new Child("1", 2);
	// 		c = childRepository.Add(c);
	// 		c2 = childRepository.Add(c2);
	// 		Debug.Assert(childRepository.GetAll().Count == initial + 2);
	// 		Debug.Assert(childRepository.GetById(c2.Id).Age == 2);
	// 		c2.Age = 1;
	// 		childRepository.Update(c2, c2.Id);
	// 		Debug.Assert(childRepository.GetById(c2.Id).Age == 1);
	//
	// 		ISignupRepository signupRepository = new SignupDBRepository(Program.props);
	// 		int initial2 = signupRepository.GetAll().Count();
	// 		Signup s = new Signup(c, AgeGroup.NINE_ELEVEN, RaceDistance.HUNDRED);
	// 		Signup s2 = new Signup(c2, AgeGroup.SIX_EIGHT, RaceDistance.THOUSAND);
	// 		s = signupRepository.Add(s);
	// 		s2 = signupRepository.Add(s2);
	// 		Debug.Assert(signupRepository.GetAll().Count() == initial2 + 2);
	// 		Debug.Assert(signupRepository.GetById(s2.Id).RaceDistance == RaceDistance.THOUSAND);
	// 		s2.RaceDistance = RaceDistance.FIFTEEN_HUNDRED;
	// 		signupRepository.Update(s2, s2.Id);
	// 		Debug.Assert(signupRepository.GetById(s2.Id).RaceDistance == RaceDistance.FIFTEEN_HUNDRED);
	// 		Debug.Assert(signupRepository.GetChildrenByRace(AgeGroup.SIX_EIGHT, RaceDistance.FIFTEEN_HUNDRED).Count == 1);
	// 		signupRepository.Delete(s.Id);
	// 		signupRepository.Delete(s2.Id);
	// 		Debug.Assert(signupRepository.GetAll().Count() == initial2);
	//
	// 		childRepository.Delete(c.Id);
	// 		childRepository.Delete(c2.Id);
	// 		Debug.Assert(childRepository.GetAll().Count == initial);
	//
	// 		IUserRepository userRepository = new UserDBRepository(Program.props);
	// 		initial = userRepository.GetAll().Count();
	// 		User u = new User("1", "2");
	// 		User u2 = new User("2", "3");
	// 		u = userRepository.Add(u);
	// 		u2 = userRepository.Add(u2);
	// 		Debug.Assert(userRepository.GetAll().Count == initial + 2);
	// 		Debug.Assert(userRepository.GetById(u2.Id).HashedPassword == "3");
	// 		Debug.Assert(userRepository.GetUserByUsername("1").HashedPassword == "2");
	// 		u2.HashedPassword = "33";
	// 		userRepository.Update(u2, u2.Id);
	// 		Debug.Assert(userRepository.GetById(u2.Id).HashedPassword == "33");
	// 		userRepository.Delete(u.Id);
	// 		userRepository.Delete(u2.Id);
	// 		Debug.Assert(userRepository.GetAll().Count == initial);
	// 	}
	//
	// }
}
