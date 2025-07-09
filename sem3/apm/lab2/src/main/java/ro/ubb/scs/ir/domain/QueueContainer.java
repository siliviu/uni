package ro.ubb.scs.ir.domain;

import java.util.ArrayList;

public class QueueContainer extends AbstractContainer {
	@Override
	public Task remove() {
		Task task = list.get(0);
		list.remove(0);
		return task;
	}
	public QueueContainer() {
	}

	public QueueContainer(ArrayList<Task> list) {
	}

}
