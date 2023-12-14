package map.lab7.util;

import map.lab7.util.Events.UpdateEvent;

public abstract class Observer {
	public abstract void update(UpdateEvent updateEvent);
}
