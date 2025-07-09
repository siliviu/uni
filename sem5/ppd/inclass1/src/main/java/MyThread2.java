public class MyThread2 extends Thread {
	int id, p;
	int[] a, b, c;

	public MyThread2(int i, int[] a, int[] b, int[] c, int p) {
		this.id = i;
		this.a = a;
		this.b = b;
		this.c = c;
		this.p = p;
	}

	public void run() {
//		System.out.println("ID: " + i);
		int n = a.length;
		for (int i = id; i < n; i += p)
			c[i] = (int) Math.sqrt(a[i] * a[i] * a[i] * a[i] * Math.sin(a[i]) + Math.log(b[i] * b[i]));
	}

}
