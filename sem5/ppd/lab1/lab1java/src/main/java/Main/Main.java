package Main;

import java.io.*;
import java.util.*;
import java.util.concurrent.*;

public class Main {
	static int N, M, n, m, P = 1;

	static int getElement(int[][] in, int i, int j) {
		int n = in.length;
		int m = in[0].length;
		i = Math.max(i, 0);
		j = Math.max(j, 0);
		i = Math.min(i, N - 1);
		j = Math.min(j, M - 1);
		return in[i][j];
	}

	static void task(int[][] in, int[][] conv, int startY, int endY, int startX, int endX, int[][] ans) {
		for (int i = startY; i < endY; ++i)
			for (int j = startX; j < endX; ++j)
				for (int di = -n / 2; di <= n / 2; ++di)
					for (int dj = -m / 2; dj <= m / 2; ++dj)
						ans[i][j] += getElement(in, i + di, j + dj) * conv[n / 2 + di][m / 2 + dj];
	}

	static void taskDistribution(int[][] in, int[][] conv, List<int[]> indexes, int[][] ans) {
		for (int[] index : indexes) {
			int i = index[0], j = index[1];
			for (int di = -n / 2; di <= n / 2; ++di)
				for (int dj = -m / 2; dj <= m / 2; ++dj)
					ans[i][j] += getElement(in, i + di, j + dj) * conv[n / 2 + di][m / 2 + dj];
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
		String type = args[1];
		String out = args[2];

		BufferedReader reader = new BufferedReader(new FileReader("data.txt"));
		String[] dimensions = reader.readLine().split(" ");
		N = Integer.parseInt(dimensions[0]);
		M = Integer.parseInt(dimensions[1]);
		n = Integer.parseInt(dimensions[2]);
		m = Integer.parseInt(dimensions[3]);
		int[][] in = new int[N][M];
		int[][] conv = new int[n][m];

		for (int i = 0; i < N; ++i) {
			String[] row = reader.readLine().split(" ");
			for (int j = 0; j < M; ++j) {
				in[i][j] = Integer.parseInt(row[j]);
			}
		}

		for (int i = 0; i < n; ++i) {
			String[] row = reader.readLine().split(" ");
			for (int j = 0; j < m; ++j) {
				conv[i][j] = Integer.parseInt(row[j]);
			}
		}

		int[][] ansDo = new int[N][M];

		test(() -> {
			if (P == 1) {
				task(in, conv, 0, N, 0, M, ansDo);
				return;
			}
			Thread[] threads = new Thread[P];
			if (type.equals("LINE")) {
				int block = N / P, remainder = N % P;
				int start = 0, end = block;
				for (int i = 0; i < P; ++i) {
					if (remainder > 0) {
						++end;
						--remainder;
					}
					int finalStart = start;
					int finalEnd = end;
					threads[i] = new Thread(() -> task(in, conv, finalStart, finalEnd, 0, M, ansDo));
					threads[i].start();
					start = end;
					end = start + block;
				}
			} else if (type.equals("COLUMN")) {
				int block = M / P, remainder = M % P;
				int start = 0, end = block;
				for (int i = 0; i < P; ++i) {
					if (remainder > 0) {
						++end;
						--remainder;
					}
					int finalStart = start;
					int finalEnd = end;
					threads[i] = new Thread(() -> task(in, conv, 0, N, finalStart, finalEnd, ansDo));
					threads[i].start();
					start = end;
					end = start + block;
				}
			} else if (type.equals("BLOCK")) {
				int blocky = (int) Math.ceil((double) N / Math.sqrt(P));
				int blockx = (int) Math.ceil((double) M / Math.sqrt(P));
				int cur = 0;
				for (int i = 0; i < N; i += blocky) {
					for (int j = 0; j < M; j += blockx) {
						int finalI = i;
						int finalJ = j;
						threads[cur] = new Thread(() -> task(in, conv, finalI, Math.min(finalI + blocky, N), finalJ, Math.min(finalJ + blockx, M), ansDo));
						threads[cur].start();
						cur++;
					}
				}
			} else if (type.equals("DISTRIBUTION")) {
				int block = (N * M) / P;
				for (int i = 0; i < P; ++i) {
					int threadNum = i;
					threads[i] = new Thread(() -> {
						List<int[]> indexes = new ArrayList<>();
						for (int k = threadNum * block; k < (threadNum + 1) * block; ++k) {
							indexes.add(new int[]{k / M, k % M});
						}
						taskDistribution(in, conv, indexes, ansDo);
					});
					threads[i].start();
				}
			}
			for (Thread thread : threads) {
				try {
					thread.join();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		});

		try (PrintWriter printer = new PrintWriter(new FileWriter(out))) {
			for (int[] row : ansDo) {
				for (int val : row) {
					printer.print(val + " ");
				}
				printer.println();
			}
		}
	}
}
