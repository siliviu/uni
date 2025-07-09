package service;

import domain.ComplexNumber;
import domain.Operation;

public abstract class ComplexExpression {
	private Operation op;
	private ComplexNumber[] nr;

	protected abstract ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b);

	public ComplexExpression(Operation _op, ComplexNumber[] _nr) {
		op = _op;
		nr = _nr;
	}

	public ComplexNumber execute() {
		ComplexNumber ans = nr[0];
		for (int i = 1; i < nr.length; ++i)
			ans = executeOneOperation(ans, nr[i]);
		return ans;
	}
}
