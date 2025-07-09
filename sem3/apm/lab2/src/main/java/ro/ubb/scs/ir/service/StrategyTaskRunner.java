package ro.ubb.scs.ir.service;

import ro.ubb.scs.ir.domain.*;

public class StrategyTaskRunner implements TaskRunner {
	private Container container;
	private final TaskContainerFactory taskContainerFactory = new TaskContainerFactory();

	public StrategyTaskRunner(Strategy strategy) {
		container = taskContainerFactory.getFactory().createContainer(strategy);
	}

	@Override
	public void executeOneTask() {
		Task t = container.remove();
		t.execute();
	}

	@Override
	public void executeAll() {
		while (hasTask())
			executeOneTask();
	}

	@Override
	public void addTask(Task t) {
		container.add(t);
	}

	@Override
	public boolean hasTask() {
		return !container.isEmpty();
	}
}
