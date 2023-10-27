package ro.ubb.scs.ir;

import ro.ubb.scs.ir.domain.*;
import ro.ubb.scs.ir.service.*;

import java.time.LocalDateTime;
import java.util.ArrayList;

public class Main {
	public static void main(String[] args) {
		Strategy strategy = args[0].equals("FIFO") ? Strategy.FIFO : Strategy.LIFO;
		StrategyTaskRunner StrategyTaskRunner = new StrategyTaskRunner(strategy);

		StrategyTaskRunner.addTask(new MessageTask("1", "2", "hi1", "me", "you", LocalDateTime.now()));
		StrategyTaskRunner.addTask(new MessageTask("2", "3", "hi2", "me", "you", LocalDateTime.now()));
		StrategyTaskRunner.addTask(new MessageTask("3", "4", "hi3", "me", "you", LocalDateTime.now()));
		StrategyTaskRunner.addTask(new MessageTask("4", "5", "hi4", "me", "you", LocalDateTime.now()));
		StrategyTaskRunner.addTask(new MessageTask("5", "6", "hi5", "me", "you", LocalDateTime.now()));
		ArrayList<Integer> a = new ArrayList<Integer>();
		a.add(7);
		a.add(6);
		a.add(4);
		a.add(5);
		a.add(3);
		a.add(1);
		StrategyTaskRunner.addTask(new SortingTask("22", "haha", new BubbleSort(), a));
		ArrayList<Integer> b = new ArrayList<Integer>();
		b.add(7);
		b.add(6);
		b.add(4);
		b.add(5);
		b.add(3);
		b.add(1);
		StrategyTaskRunner.addTask(new SortingTask("22", "haha", new MergeSort(), b));
//		TaskRunner taskRunner = new PrinterTaskRunner(StrategyTaskRunner);
//		taskRunner.executeAll();
		TaskRunner taskRunner = new PrinterTaskRunner(new DelayTaskRunner(StrategyTaskRunner));
		taskRunner.executeAll();
	}
}
