package ro.ubb.scs.ir.domain;

public interface Container {
	Task remove();

	void add(Task task);

	int size();

	boolean isEmpty();
}
