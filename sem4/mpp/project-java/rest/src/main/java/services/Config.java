package services;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import repository.SignupDBRepository;
import repository.SignupHibernateDBRepository;
import repository.SignupRepository;
import repository.UserDBRepository;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

@Configuration
public class Config {
//	@Bean
//	Properties getProps() {
//		Properties props = new Properties();
//		try {
//			props.load(new FileReader("./bd.config"));
//		} catch (IOException e) {
//			System.out.println("Cannot find bd.config" + e);
//		}
//		return props;
//	}

	@Bean
	SignupRepository SignupRepository() {
		return new SignupHibernateDBRepository();
	}
}
