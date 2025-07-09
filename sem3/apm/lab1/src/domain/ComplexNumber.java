package domain;

import java.text.DecimalFormat;

public class ComplexNumber {
	private final double re, im;
	public ComplexNumber(double _re, double _im) {
		re = _re;
		im = _im;
	}

	public static ComplexNumber add(ComplexNumber a, ComplexNumber b) {
		return new ComplexNumber(a.re + b.re, a.im + b.im);
	}

	public static ComplexNumber subtract(ComplexNumber a, ComplexNumber b) {
		return new ComplexNumber(a.re - b.re, a.im - b.im);
	}

	public static ComplexNumber multiply(ComplexNumber a, ComplexNumber b) {
		return new ComplexNumber(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
	}

	public static ComplexNumber conjugate(ComplexNumber a) {
		return new ComplexNumber(a.re, -a.im);
	}

	public static ComplexNumber divide(ComplexNumber a, ComplexNumber b) {
		return multiply(new ComplexNumber(a.re / (b.re * b.re + b.im * b.im), a.im / (b.re * b.re + b.im * b.im)), conjugate(b));
	}
	public static final DecimalFormat df = new DecimalFormat( "#.#####" );
	@Override
	public String toString() {
		if (re == 0 && im == 0)
			return "0";
		String r = "";
		if (re != 0)
			r += df.format(re);
		if (im != 0) {
			if (im > 0 && re != 0)
				r += "+";
			r += df.format(im);
			r += "*i";
		}
		return r;
	}

	public void print() {
		System.out.print(this.toString());
	}
}
