package service;

import domain.ComplexNumber;
import domain.Operation;

public class Subtraction extends ComplexExpression {
	public Subtraction(Operation _op, ComplexNumber[] _nr) {
		super(_op, _nr);
	}

	@Override
	protected ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b) {
		return ComplexNumber.subtract(a, b);
	}
}
