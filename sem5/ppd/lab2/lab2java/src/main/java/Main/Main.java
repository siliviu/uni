package Main;

import java.io.*;
import java.util.*;
import java.util.concurrent.*;

public class Main {
	static int N, M, n, m, P = 1;
	static CyclicBarrier barrier;

	static int getElement(int[][] mat, int i, int j) {
		i = Math.max(i, 0);
		j = Math.max(j, 0);
		i = Math.min(i, N - 1);
		j = Math.min(j, M - 1);
		return mat[i][j];
	}

	static void task(int[][] mat, int[][] conv, int startY, int endY) {
		int[] up = Arrays.copyOf(mat[Math.max(startY - 1, 0)], M);
		int[] down = Arrays.copyOf(mat[Math.min(endY, N - 1)], M);

		for (int i = startY; i < endY; ++i) {
			int[] newUp = Arrays.copyOf(mat[i], M);

			for (int j = 0; j < M; ++j) {
				mat[i][j] = 0;

				for (int di = -n / 2; di <= n / 2; ++di) {
					for (int dj = -m / 2; dj <= m / 2; ++dj) {
						int val;
						if (di == -1) {
							val = up[Math.min(Math.max(0, j + dj), M - 1)];
						} else if (di == 0) {
							val = newUp[Math.min(Math.max(0, j + dj), M - 1)];
						} else if (i == endY - 1 && di == 1) {
							val = down[Math.min(Math.max(0, j + dj), M - 1)];
						} else {
							val = getElement(mat, i + di, j + dj);
						}
						mat[i][j] += val * conv[n / 2 + di][m / 2 + dj];
					}
				}
			}
			up = newUp;
		}
	}

	static void taskParallel(int[][] mat, int[][] conv, int startY, int endY) {
		try {
			int[] up = Arrays.copyOf(mat[Math.max(startY - 1, 0)], M);
			int[] down = Arrays.copyOf(mat[Math.min(endY, N - 1)], M);
			barrier.await();

			for (int i = startY; i < endY; ++i) {
				int[] newUp = Arrays.copyOf(mat[i], M);

				for (int j = 0; j < M; ++j) {
					mat[i][j] = 0;

					for (int di = -n / 2; di <= n / 2; ++di) {
						for (int dj = -m / 2; dj <= m / 2; ++dj) {
							int val;
							if (di == -1) {
								val = up[Math.min(Math.max(0, j + dj), M - 1)];
							} else if (di == 0) {
								val = newUp[Math.min(Math.max(0, j + dj), M - 1)];
							} else if (i == endY - 1 && di == 1) {
								val = down[Math.min(Math.max(0, j + dj), M - 1)];
							} else {
								val = getElement(mat, i + di, j + dj);
							}
							mat[i][j] += val * conv[n / 2 + di][m / 2 + dj];
						}
					}
				}
				up = newUp;
			}
		} catch (InterruptedException | BrokenBarrierException e) {
			e.printStackTrace();
		}
	}

	static void test(Runnable function) {
		long tStart = System.nanoTime();
		function.run();
		long tEnd = System.nanoTime();
		long elapsedTimeMs = (tEnd - tStart);
		System.out.printf("%d\n", elapsedTimeMs);
	}

	public static void main(String[] args) throws IOException {
		P = Integer.parseInt(args[0]);
		String outputFileName = args[1];

		BufferedReader reader = new BufferedReader(new FileReader("data.txt"));
		String[] dimensions = reader.readLine().split(" ");
		N = Integer.parseInt(dimensions[0]);
		M = Integer.parseInt(dimensions[1]);
		n = Integer.parseInt(dimensions[2]);
		m = Integer.parseInt(dimensions[3]);

		int[][] mat = new int[N][M];
		int[][] conv = new int[n][m];

		for (int i = 0; i < N; ++i) {
			String[] row = reader.readLine().split(" ");
			for (int j = 0; j < M; ++j) {
				mat[i][j] = Integer.parseInt(row[j]);
			}
		}
		for (int i = 0; i < n; ++i) {
			String[] row = reader.readLine().split(" ");
			for (int j = 0; j < m; ++j) {
				conv[i][j] = Integer.parseInt(row[j]);
			}
		}

		test(() -> {
			try {
				if (P == 1) {
					task(mat, conv, 0, N);
					return;
				}
				barrier = new CyclicBarrier(P);
				Thread[] threads = new Thread[P];
				int block = N / P, remainder = N % P;
				int startY = 0, endY = block;

				for (int i = 0; i < P; ++i) {
					if (remainder > 0) {
						endY++;
						remainder--;
					}
					int finalStartY = startY;
					int finalEndY = endY;

					threads[i] = new Thread(() -> taskParallel(mat, conv, finalStartY, finalEndY));
					threads[i].start();
					startY = endY;
					endY = startY + block;
				}
				for (Thread thread : threads) {
					thread.join();
				}
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		});

		try (PrintWriter printer = new PrintWriter(new FileWriter(outputFileName))) {
			for (int[] row : mat) {
				for (int val : row) {
					printer.print(val + " ");
				}
				printer.println();
			}
		}
	}
}
