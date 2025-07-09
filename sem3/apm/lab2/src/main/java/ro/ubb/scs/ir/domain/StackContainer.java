package ro.ubb.scs.ir.domain;

import java.util.ArrayList;

public class StackContainer extends AbstractContainer {
	@Override
	public Task remove() {
		Task task = list.get(list.size() - 1);
		list.remove(list.size() - 1);
		return task;
	}
	public StackContainer() {
	}
	public StackContainer(ArrayList<Task> list) {
	}

}
