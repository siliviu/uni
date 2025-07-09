package ro.ubb.scs.ir.service;

import ro.ubb.scs.ir.domain.Task;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class DelayTaskRunner extends AbstractTaskRunner {
	public static final DateTimeFormatter dtf = DateTimeFormatter.ofPattern("dd/MM/yyyy hh:mm");


	public DelayTaskRunner(TaskRunner taskRunner) {
		super(taskRunner);
	}

	@Override
	public void executeOneTask() {
		try {
			Thread.sleep(3000);
			super.executeOneTask();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

}
