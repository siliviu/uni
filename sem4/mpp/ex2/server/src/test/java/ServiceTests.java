import org.junit.jupiter.api.Test;
import server.LoginService;

import java.io.FileReader;
import java.io.IOException;
import java.util.Properties;

import static org.junit.jupiter.api.Assertions.assertDoesNotThrow;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class ServiceTests {
	@Test
	public void LoginTest() {
		Properties props = new Properties();
		try {
			props.load(new FileReader("bd.config"));
		} catch (IOException e) {
			System.out.println("Cannot find bd.config " + e);
		}
		LoginService loginService = new LoginService(new UserDBRepository(props));
		assertThrows(RuntimeException.class, () -> loginService.register("ana", "1234"));
		assertDoesNotThrow(() -> loginService.login("ana", "1234"));
		assertThrows(RuntimeException.class, () -> loginService.login("ana", "12345"));

	}
}
