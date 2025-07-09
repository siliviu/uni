package service;

import domain.ComplexNumber;
import domain.Operation;

public class Addition extends ComplexExpression {
	public Addition(Operation _op, ComplexNumber[] _nr) {
		super(_op, _nr);
	}

	@Override
	protected ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b) {
		return ComplexNumber.add(a, b);
	}
}
