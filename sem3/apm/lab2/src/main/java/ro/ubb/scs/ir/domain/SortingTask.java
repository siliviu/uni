package ro.ubb.scs.ir.domain;

import ro.ubb.scs.ir.domain.Task;
import ro.ubb.scs.ir.service.AbstractSorter;

import java.util.ArrayList;

public class SortingTask extends Task {
	private final AbstractSorter sorter;
	private final ArrayList<Integer> list;
	public SortingTask(String taskID, String desc, AbstractSorter sorter, ArrayList<Integer> list) {
		super(taskID, desc);
		this.sorter = sorter;
		this.list = list;
	}

	@Override
	public void execute() {
		sorter.sort(list);
		System.out.println(list);
	}
}
