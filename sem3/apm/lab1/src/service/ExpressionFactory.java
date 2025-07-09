package service;

import domain.*;

public class ExpressionFactory {
	private static final ExpressionFactory expression = new ExpressionFactory();

	private ExpressionFactory() {
	}

	public static ExpressionFactory getExpression(){
		return expression;
	}

	public ComplexExpression createExpression(Operation operation, ComplexNumber[] args) {
		if (operation == Operation.ADDITION)
			return new Addition(operation, args);
		else if (operation == Operation.SUBTRACTION)
			return new Subtraction(operation, args);
		else if (operation == Operation.MULTIPLICATION)
			return new Multiplication(operation, args);
		else
			return new Division(operation, args);
	}
}
