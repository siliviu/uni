package utils;

import domain.Child;
import domain.Signup;
import domain.User;
import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;

public class HibernateUtils {

	private static SessionFactory sessionFactory;

	public static SessionFactory getSessionFactory() {
		if ((sessionFactory == null) || (sessionFactory.isClosed()))
			sessionFactory = createNewSessionFactory();
		return sessionFactory;
	}

	private static SessionFactory createNewSessionFactory() {
		sessionFactory = new Configuration()
				.configure("hibernate.cfg.xml")
				.addAnnotatedClass(User.class)
				.addAnnotatedClass(Child.class)
				.addAnnotatedClass(Signup.class)
				.buildSessionFactory();
		return sessionFactory;
	}

	public static void closeSessionFactory() {
		if (sessionFactory != null)
			sessionFactory.close();
	}
}
