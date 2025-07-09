package ro.ubb.scs.ir.service;

import ro.ubb.scs.ir.domain.Task;

public interface TaskRunner {
	void executeOneTask();
	void executeAll();
	void addTask(Task t);
	boolean hasTask();
}
