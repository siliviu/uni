import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class Main {

	static int[] generateVector(int length, int upperBound) {
		Random random = new Random();
		int[] ans = new int[length];
		for (int i = 0; i < length; ++i)
			ans[i] = random.nextInt(upperBound);
		return ans;
	}

	static int[] addVectorsSerial(int[] a, int[] b) {
		int n = a.length;
		int[] c = new int[n];
		for (int i = 0; i < n; ++i)
			c[i] = (int) Math.sqrt(a[i] * a[i] * a[i] * a[i] * Math.sin(a[i]) + Math.log(b[i] * b[i]));
		return c;
	}

	static int[] addVectorParallel1(int[] a, int[] b) {
		int n = a.length;
		int[] c = new int[n];

		MyThread[] threads = new MyThread[P];
		int block = N / P;
		int start = 0, end = block;
		int remainder = N % P;

		for (int i = 0; i < P; ++i) {
			if (remainder > 0) {
				++end;
				--remainder;
			}
			threads[i] = new MyThread(i, a, b, c, start, end);
			threads[i].start();
			start = end;
			end = start + block;
		}
		for (int i = 0; i < P; ++i) {
			try {
				threads[i].join();
			} catch (InterruptedException e) {
				throw new RuntimeException(e);
			}
		}
		return c;
	}

	static int[] addVectorParallel2(int[] a, int[] b) {
		int n = a.length;
		int[] c = new int[n];

		MyThread2[] threads = new MyThread2[P];

		for (int i = 0; i < P; ++i) {
			threads[i] = new MyThread2(i, a, b, c, P);
			threads[i].start();
		}
		for (int i = 0; i < P; ++i) {
			try {
				threads[i].join();
			} catch (InterruptedException e) {
				throw new RuntimeException(e);
			}
		}
		return c;
	}

	final static int N = 50000000, MAX = 100000000, P = 16;

	public static void main(String[] args) {
		int[] a = generateVector(N, MAX);
		int[] b = generateVector(N, MAX);
		var t1 = System.currentTimeMillis();
		int[] cSerial = addVectorsSerial(a, b);
		var t2 = System.currentTimeMillis();
		System.out.println(t2 - t1);
		//		System.out.println("a: " + Arrays.toString(a));
		//		System.out.println("b: " + Arrays.toString(b));
		//		System.out.println("a+b serial: " + Arrays.toString(cSerial));
		t1 = System.currentTimeMillis();
		int[] cParallel1 = addVectorParallel1(a, b);
		t2 = System.currentTimeMillis();
		System.out.println(Arrays.equals(cSerial, cParallel1));
		System.out.println(t2 - t1);

		t1 = System.currentTimeMillis();
		int[] cParallel2 = addVectorParallel2(a, b);
		t2 = System.currentTimeMillis();
		System.out.println(Arrays.equals(cSerial, cParallel2));
		System.out.println(t2 - t1);
	}
}
