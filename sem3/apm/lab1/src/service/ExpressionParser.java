package service;

import domain.ComplexNumber;
import domain.Operation;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ExpressionParser {
	private ComplexExpression e = null;

	public ExpressionParser(String[] args) {
		if (args.length < 3 || args.length % 2 != 1)
			return;
		int n = args.length;
		String op = args[1];
		for (int i = 3; i < n; i += 2)
			if (!op.equals(args[i]))
				return;
		Operation operation;
		switch (op) {
			case "+" -> operation = Operation.ADDITION;
			case "-" -> operation = Operation.SUBTRACTION;
			case "*" -> operation = Operation.MULTIPLICATION;
			case ("/") -> operation = Operation.DIVISION;
			default -> {
				return;
			}
		}
		ComplexNumber[] nrs = new ComplexNumber[(n + 1) / 2];
		for (int i = 0; i < n; i += 2) {
			Pattern p = Pattern.compile("^(-?[0-9]+(\\.[0-9]?)?)?((\\+|-|^)[0-9]+(\\.[0-9]?)?\\*i)?$");
			Matcher m = p.matcher(args[i]);
			if (m.find()) {
				double re = m.group(1) == null ? 0 : Double.parseDouble(m.group(1)), im = m.group(3) == null ? 0 : Double.parseDouble(m.group(3).substring(0, m.group(3).length() - 2));
				nrs[i / 2] = new ComplexNumber(re, im);
			} else
				return;
		}
		e = ExpressionFactory.getExpression().createExpression(operation, nrs);
	}

	public Boolean valid() {
		return e != null;
	}

	public ComplexExpression getExpression() {
		return e;
	}
}