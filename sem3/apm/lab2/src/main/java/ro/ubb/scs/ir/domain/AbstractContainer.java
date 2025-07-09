package ro.ubb.scs.ir.domain;

import ro.ubb.scs.ir.domain.Container;
import ro.ubb.scs.ir.domain.Task;

import java.util.ArrayList;

public abstract class AbstractContainer implements Container {
	protected final ArrayList<Task> list = new ArrayList<>();

	public void add(Task task) {
		list.add(task);
	}

	public int size() {
		return list.size();
	}

	public boolean isEmpty() {
		return size() == 0;
	}
}
