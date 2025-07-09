package ro.ubb.scs.ir.domain;

public abstract class Task {
	private String taskID, desc;

	public Task(String taskID, String desc) {
		this.taskID = taskID;
		this.desc = desc;
	}

	@Override
	public String toString() {
		return taskID + " " + desc;
	}

	@Override
	public int hashCode() {
		return super.hashCode();
	}

	@Override
	public boolean equals(Object obj) {
		return super.equals(obj);
	}

	public String getTaskID() {
		return taskID;
	}

	public void setTaskID(String taskID) {
		this.taskID = taskID;
	}

	public String getDesc() {
		return desc;
	}

	public void setDesc(String desc) {
		this.desc = desc;
	}

	public abstract void execute();
}
