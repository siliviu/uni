package repository;

import domain.*;
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
				.addAnnotatedClass(User.class)
				.addAnnotatedClass(Ward.class)
				.addAnnotatedClass(Medicine.class)
				.addAnnotatedClass(Order.class)
				.addAnnotatedClass(OrderItem.class)
				.buildSessionFactory();
		return sessionFactory;
	}

	public static void closeSessionFactory() {
		if (sessionFactory != null)
			sessionFactory.close();
	}
}
