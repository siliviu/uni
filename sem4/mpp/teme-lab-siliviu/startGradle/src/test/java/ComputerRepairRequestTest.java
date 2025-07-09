import model.ComputerRepairRequest;
import org.junit.jupiter.api.DisplayName;
import org.junit.jupiter.api.Test;
import repository.RequestRepository;

import java.lang.reflect.Array;
import java.util.ArrayList;

import static org.junit.jupiter.api.Assertions.*;


public class ComputerRepairRequestTest {
	@Test
	@DisplayName("First test")
	public void testExample() {
		ComputerRepairRequest crr = new ComputerRepairRequest();
		RequestRepository repository = new RequestRepository();
		assertEquals(0, repository.getAll().size());
		repository.add(crr);
		assertEquals(1, repository.getAll().size());
	}


	@Test
	@DisplayName("Second test")
	public void testExample2() {
		ComputerRepairRequest crr = new ComputerRepairRequest();
		RequestRepository repository = new RequestRepository();
		repository.add(crr);
		assertEquals(1, repository.getAll().size());
		repository.delete(crr);
		assertEquals(0, repository.getAll().size());
	}

	@Test
	@DisplayName("Third test")
	public void testExample3() {
		ComputerRepairRequest crr = new ComputerRepairRequest(1, "1", "1", "1", "1", "1", "1");
		ComputerRepairRequest crr2 = new ComputerRepairRequest(2, "2", "1", "1", "1", "1", "1");
		ComputerRepairRequest crr3 = new ComputerRepairRequest(3, "3", "1", "1", "1", "1", "1");
		ComputerRepairRequest crr4 = new ComputerRepairRequest(4, "4", "1", "1", "1", "1", "1");
		RequestRepository repository = new RequestRepository();
		repository.add(crr);
		repository.add(crr2);
		repository.add(crr3);
		repository.add(crr4);
		assertThrows(RuntimeException.class, ()->repository.findById(11));
		assertEquals(crr,repository.findById(1));
		crr2.setID(1);
		repository.update(crr2,1);
		assertEquals(crr2,repository.findById(1));
		repository.delete(crr3);
		repository.delete(crr4);
		assertEquals(2, repository.getAll().size());
	}
}
