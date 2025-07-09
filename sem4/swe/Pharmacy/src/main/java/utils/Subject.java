package utils;

import java.util.ArrayList;
import java.util.List;

public class Subject {
	private final List<Observer> observers = new ArrayList<>();
	public void addObserver(Observer observer){
		observers.add(observer);
	}
	public void broadcast(UpdateEvent updateEvent){
		for(Observer observer : observers)
			observer.update(updateEvent);
	}
}
