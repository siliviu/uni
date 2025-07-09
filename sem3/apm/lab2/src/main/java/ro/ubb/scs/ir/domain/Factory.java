package ro.ubb.scs.ir.domain;

public interface Factory {
	Container createContainer(Strategy strategy);
}
