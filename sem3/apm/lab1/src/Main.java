import service.ComplexExpression;
import domain.ComplexNumber;
import service.ExpressionParser;

public class Main {
	public static void main(String[] args) {
		ExpressionParser ep = new ExpressionParser(args);
		if(!ep.valid())
			System.out.println("Invalid expression");
		else {
			ComplexExpression expr = ep.getExpression();
			ComplexNumber result = expr.execute();
			result.print();
		}
	}
}