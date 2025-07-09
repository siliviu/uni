package services;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import repository.*;
import server.LoginService;
import server.MasterService;

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

//	@Bean
//	GameRepository GameRepository() {
//		return new GameHibernateRepository();
//	}
	@Bean
	MasterService MasterService(){
		UserRepository userRepository = new UserHibernateRepository();
		GameRepository gameRepository = new GameHibernateRepository();
		WordsRepository wordsRepository = new WordsHibernateRepository();
		MoveRepository moveRepository = new MoveHibernateRepository();
		LoginService loginService = new LoginService(userRepository);
		return new MasterService(loginService, gameRepository, wordsRepository, moveRepository);
	}
}
