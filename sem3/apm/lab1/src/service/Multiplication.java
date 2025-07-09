package service;

import domain.ComplexNumber;
import domain.Operation;

public class Multiplication extends ComplexExpression {
	public Multiplication(Operation _op, ComplexNumber[] _nr) {
		super(_op, _nr);
	}

	@Override
	protected ComplexNumber executeOneOperation(ComplexNumber a, ComplexNumber b) {
		return ComplexNumber.multiply(a, b);
	}
}
