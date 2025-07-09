package services;

import domain.Signup;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.actuate.web.exchanges.HttpExchange;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import repository.SignupRepository;

import java.util.Collection;

@CrossOrigin
@RestController
@RequestMapping("/competition/signups")
public class SignupController {
	@Autowired
	SignupRepository signupRepository;

	@GetMapping
	public Collection<Signup> get() {
		return signupRepository.getAll();
	}

	@GetMapping(value = "/{id}")
	public ResponseEntity<?> getById(@PathVariable Integer id) {
		Signup signup = signupRepository.getById(id);
		if (signup == null)
			return new ResponseEntity<>("Signup not found", HttpStatus.NOT_FOUND);
		return new ResponseEntity<>(signup, HttpStatus.OK);
	}

	@PostMapping
	public ResponseEntity<?> add(@RequestBody Signup signup) {
		try {
			return new ResponseEntity<>(signupRepository.add(signup), HttpStatus.OK);
		} catch (Exception e) {
			return new ResponseEntity<>(e.getMessage(), HttpStatus.BAD_REQUEST);
		}
	}

	@PutMapping(value = "/{id}")
	public ResponseEntity<?> update(@RequestBody Signup signup, @PathVariable Integer id) {
		if (signupRepository.getById(id) == null)
			return new ResponseEntity<>("Signup not found", HttpStatus.NOT_FOUND);
		try {
			signupRepository.update(signup, id);
		} catch (Exception e) {
			return new ResponseEntity<>(e.getMessage(), HttpStatus.BAD_REQUEST);
		}
		return new ResponseEntity<>(signupRepository.getById(id), HttpStatus.OK);
	}

	@DeleteMapping(value = "/{id}")
	public HttpStatus remove(@PathVariable Integer id) {
		if (signupRepository.getById(id) == null)
			return HttpStatus.NOT_FOUND;
		signupRepository.delete(id);
		return HttpStatus.OK;
	}
}
