package com.example.template.util;

import com.example.template.util.events.UpdateEvent;

public abstract class Observer {
	public abstract void update(UpdateEvent updateEvent);
}
