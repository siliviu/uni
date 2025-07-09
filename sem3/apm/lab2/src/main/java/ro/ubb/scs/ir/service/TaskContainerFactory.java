package ro.ubb.scs.ir.service;

import ro.ubb.scs.ir.domain.*;

public class TaskContainerFactory implements Factory {
	private static final TaskContainerFactory taskFactory = new TaskContainerFactory();

	public TaskContainerFactory getFactory() {
		return taskFactory;
	}

	@Override
	public Container createContainer(Strategy strategy) {
		if (strategy == Strategy.LIFO)
			return new StackContainer();
		return new QueueContainer();
	}
}
