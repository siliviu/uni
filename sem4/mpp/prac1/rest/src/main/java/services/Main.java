package services;


import org.apache.activemq.ActiveMQConnectionFactory;
import org.apache.activemq.command.ActiveMQQueue;
import org.apache.activemq.command.ActiveMQTopic;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import javax.jms.*;

@SpringBootApplication
public class Main {
	public static void main(String[] args) {
		SpringApplication.run(Main.class, args);
	}
}

