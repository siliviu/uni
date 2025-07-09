package services;

import domain.Configuration;
import domain.Game;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import server.MasterService;

import java.util.ArrayList;
import java.util.List;

@CrossOrigin
@org.springframework.web.bind.annotation.RestController
@RequestMapping("/app")
public class RestController {
	@Autowired
	MasterService masterService;
	@GetMapping("games")
	public ResponseEntity<?> get(@RequestParam String user) {
		List<Game> game = new ArrayList<>();
		try {
			game = masterService.getGuesses(user);
		} catch (Exception e) {
			return new ResponseEntity<>(e.getMessage(), HttpStatus.BAD_REQUEST);
		}
		if (game == null)
			return new ResponseEntity<>("No games found", HttpStatus.NOT_FOUND);
		return new ResponseEntity<>(game, HttpStatus.OK);
	}

	@PostMapping("configurations")
	public ResponseEntity<?> updateConfiguration(@RequestBody Configuration configuration) {
		try {
			masterService.addConfiguration(configuration);
		} catch (Exception e) {
			return new ResponseEntity<>(e.getMessage(), HttpStatus.BAD_REQUEST);
		}
		return new ResponseEntity<>("Configuration successfully added: " + configuration, HttpStatus.OK);
	}
}
