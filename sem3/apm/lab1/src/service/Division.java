package service;

import domain.ComplexNumber;
import domain.Operation;

public class Division extends ComplexExpression {
	public Division(Operation _op, ComplexNumber[] _nr) {
		super(_op, _nr);
	}

	@Override
	protected ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b) {
		return ComplexNumber.divide(a, b);
	}
}
