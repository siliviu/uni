package ro.ubb.scs.ir.service;

import ro.ubb.scs.ir.domain.Task;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class PrinterTaskRunner extends AbstractTaskRunner {
	public static final DateTimeFormatter dtf = DateTimeFormatter.ofPattern("dd/MM/yyyy hh:mm");


	public PrinterTaskRunner(TaskRunner taskRunner) {
		super(taskRunner);
	}

	@Override
	public void executeOneTask() {
		super.executeOneTask();
		System.out.println("Executed at " + dtf.format(LocalDateTime.now()));
	}

}
