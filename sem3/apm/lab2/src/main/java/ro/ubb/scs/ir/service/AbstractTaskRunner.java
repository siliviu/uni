package ro.ubb.scs.ir.service;

import ro.ubb.scs.ir.domain.Container;
import ro.ubb.scs.ir.domain.Strategy;
import ro.ubb.scs.ir.domain.Task;

public abstract class AbstractTaskRunner implements TaskRunner {
	private final TaskRunner taskRunner;

	@Override
	public void executeOneTask() {
		taskRunner.executeOneTask();
	}

	@Override
	public void executeAll() {
		while (hasTask())
			executeOneTask();
	}

	@Override
	public void addTask(Task t) {
		taskRunner.addTask(t);
	}

	@Override
	public boolean hasTask() {
		return taskRunner.hasTask();
	}

	protected AbstractTaskRunner(TaskRunner taskRunner) {
		this.taskRunner = taskRunner;
	}
}
