import java.sql.SQLOutput;

public class MyThread extends Thread {
	int i, start, end;
	int[] a, b, c;

	public MyThread(int i, int[] a, int[] b, int[] c, int start, int end) {
		this.i = i;
		this.a = a;
		this.b = b;
		this.c = c;
		this.start = start;
		this.end = end;
	}

	public void run() {
//		System.out.println("ID: " + i);
		for (int i = start; i < end; ++i)
			c[i] = (int) Math.sqrt(a[i] * a[i] * a[i] * a[i] * Math.sin(a[i]) + Math.log(b[i] * b[i]));
	}

}
