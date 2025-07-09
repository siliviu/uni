package services;

import domain.Game;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import server.MasterService;

@CrossOrigin
@org.springframework.web.bind.annotation.RestController
@RequestMapping("/app/games")
public class RestController {
	@Autowired
	MasterService masterService;
//
//	@GetMapping
//	public Collection<Game> get(int id) {
//		return masterService.get();
//	}

	@GetMapping(value = "?user={id}&outcome=win")
	public ResponseEntity<?> get(@PathVariable Integer id) {
		Game game = masterService.getGame(id);
		if (game == null)
			return new ResponseEntity<>("Game not found", HttpStatus.NOT_FOUND);
		return new ResponseEntity<>(game, HttpStatus.OK);
	}

	@PutMapping(value = "{id}/configuration")
	public ResponseEntity<?> updateConfiguration(@PathVariable Integer id, @RequestBody String configuration) {
		Game game = masterService.getGame(id);
		if (game == null)
			return new ResponseEntity<>("Game not found", HttpStatus.NOT_FOUND);
		try {
			masterService.changeConfiguration(game, configuration);
		} catch (Exception e) {
			return new ResponseEntity<>(e.getMessage(), HttpStatus.BAD_REQUEST);
		}
		return new ResponseEntity<>("Configuration successfully changed to: "+configuration, HttpStatus.OK);
	}
//
//	@PostMapping
//	public ResponseEntity<?> add(@RequestBody Signup signup) {
//		try {
//			return new ResponseEntity<>(signupRepository.add(signup), HttpStatus.OK);
//		} catch (Exception e) {
//			return new ResponseEntity<>(e.getMessage(), HttpStatus.BAD_REQUEST);
//		}
//	}
//
//	@PutMapping(value = "/{id}")
//	public ResponseEntity<?> update(@RequestBody Signup signup, @PathVariable Integer id) {
//		if (signupRepository.getById(id) == null)
//			return new ResponseEntity<>("Signup not found", HttpStatus.NOT_FOUND);
//		try {
//			signupRepository.update(signup, id);
//		} catch (Exception e) {
//			return new ResponseEntity<>(e.getMessage(), HttpStatus.BAD_REQUEST);
//		}
//		return new ResponseEntity<>(signupRepository.getById(id), HttpStatus.OK);
//	}
//
//	@DeleteMapping(value = "/{id}")
//	public HttpStatus remove(@PathVariable Integer id) {
//		if (signupRepository.getById(id) == null)
//			return HttpStatus.NOT_FOUND;
//		signupRepository.delete(id);
//		return HttpStatus.OK;
//	}
}
