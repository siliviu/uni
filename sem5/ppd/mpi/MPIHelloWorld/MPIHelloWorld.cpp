#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>

using namespace std;

void print(int* a, int n) {
	for (int i = 0; i < n; ++i)
		printf("%d ", a[i]);
	printf("\n");
}

//mpiexec -n 6 .\MPIHelloWorld.exe

//int main(int argc, char** argv) {
//
//	MPI_Init(&argc, &argv);
//
//	const int N = 10, UPBOUND = 10;
//	int numbers[N], b[N], answer[N];
//
//	int world_rank, world_size;
//	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
//
//	MPI_Status status;
//	int P = world_size - 1;
//	int start, end;
//	if (world_rank == 0) {
//		for (int i = 0; i < N; ++i) {
//			numbers[i] = rand() % UPBOUND;
//			b[i] = rand() % UPBOUND;
//		}
//		//print(numbers, N);
//		//print(b, N);
//		int block = N / P, remainder = N % P;
//		start = 0, end = block;
//		for (int i = 1; i < world_size; ++i) {
//			if (remainder) {
//				++end;
//				--remainder;
//			}
//			MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
//			MPI_Send(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
//			MPI_Send(numbers + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
//			MPI_Send(b + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
//			start = end, end = start + block;
//		}
//
//		for (int i = 1; i < world_size; ++i) {
//			MPI_Recv(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
//			MPI_Recv(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
//			MPI_Recv(answer + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
//		}
//		print(numbers, N);
//		print(b, N);
//		print(answer, N);
//	}
//	else {
//		MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
//		MPI_Recv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
//		MPI_Recv(numbers + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
//		MPI_Recv(b + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
//		for (int i = start; i < end; ++i)
//			answer[i] = numbers[i] + b[i];
//		MPI_Send(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
//		MPI_Send(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
//		MPI_Send(answer + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD);
//	}
//
//	MPI_Finalize();
//}

//int main(int argc, char** argv) {
//	MPI_Init(&argc, &argv);
//
//	const int N = 10, UPBOUND = 10;
//	int numbers[N], b[N], answer[N];
//	int world_rank, world_size;
//
//	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
//
//	int P = world_size;
//	int* counts = new int[P], * displs = new int[P];
//	int block = N / P;
//	int remainder = N % P;
//
//	for (int i = 0; i < P; ++i) {
//		counts[i] = block + (i < remainder ? 1 : 0);
//		displs[i] = i == 0 ? 0 : displs[i - 1] + counts[i - 1];
//	}
//
//	int* local_a = new int[counts[world_rank]];
//	int* local_b = new int[counts[world_rank]];
//	int* local_c = new int[counts[world_rank]];
//
//	if (world_rank == 0) {
//		for (int i = 0; i < N; ++i) {
//			numbers[i] = rand() % UPBOUND;
//			b[i] = rand() % UPBOUND;
//		}
//		print(numbers, N);
//		print(b, N);
//	}
//
//	MPI_Scatterv(numbers, counts, displs, MPI_INT, local_a, counts[world_rank], MPI_INT, 0, MPI_COMM_WORLD);
//	MPI_Scatterv(b, counts, displs, MPI_INT, local_b, counts[world_rank], MPI_INT, 0, MPI_COMM_WORLD);
//
//	for (int i = 0; i < counts[world_rank]; ++i) {
//		local_c[i] = local_a[i] + local_b[i];
//	}
//
//	MPI_Gatherv(local_c, counts[world_rank], MPI_INT, answer, counts, displs, MPI_INT, 0, MPI_COMM_WORLD);
//
//	if (world_rank == 0) {
//		print(answer, N);
//	}
//
//	MPI_Finalize();
//	return 0;
//}

//int main(int argc, char** argv) {
//
//	MPI_Init(&argc, &argv);
//
//	const int N = 10, UPBOUND = 10;
//	int numbers[N], b[N], answer[N];
//
//	int world_rank, world_size;
//	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
//	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
//
//
//
//	int chunkSize = N / world_size;
//	int* auxA = new int[chunkSize];
//	int* auxB = new int[chunkSize];
//	int* auxC = new int[chunkSize];
//
//	if (world_rank == 0) {
//		for (int i = 0; i < N; ++i) {
//			numbers[i] = rand() % UPBOUND;
//			b[i] = rand() % UPBOUND;
//		}
//	}
//	MPI_Scatter(numbers, chunkSize, MPI_INT, auxA, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);
//	MPI_Scatter(b, chunkSize, MPI_INT, auxB, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);
//	for (int i = 0; i < chunkSize; ++i)
//		auxC[i] = auxA[i] + auxB[i];
//	MPI_Gather(auxC, chunkSize, MPI_INT, answer, chunkSize, MPI_INT, 0, MPI_COMM_WORLD);
//
//	if (world_rank == 0) {
//		print(numbers, N);
//		print(b, N);
//		print(answer, N);
//	}
//
//	MPI_Finalize();
//}

int sum_digits(int x) {
	int sum = 0;
	while (x) {
		sum += x % 10;
		x /= 10;
	}
	return sum;
}

int main(int argc, char** argv) {

	MPI_Init(&argc, &argv);

	//const int N = 10;
	const int N = 1'000'000;
	int* numbers = new int[N], * answer = new int[N], A = 0, B = 0;

	int world_rank, world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	MPI_Status status;
	int P = world_size - 1;
	int x;
	int start, end;
	if (world_rank == 0) {
		cin >> x;
		//ifstream cin("numbers.txt");
		//ifstream cin("numbers_small.txt");
		ifstream cin("numbers_large.txt");
		for (int i = 0; i < N; ++i) {
			cin >> numbers[i];
		}
		cin.close();
		int block = N / P, remainder = N % P;
		start = 0, end = block;
		for (int i = 1; i < world_size; ++i) {
			if (remainder) {
				++end;
				--remainder;
			}
			MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);
			MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			MPI_Send(numbers + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
			start = end, end = start + block;
		}

		for (int i = 1; i < world_size; ++i) {
			MPI_Recv(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			MPI_Recv(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			MPI_Recv(answer + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
		}
		ofstream cout("result.txt");
		for (int i = 0; i < N; ++i)
			cout << answer[i] << '\n';
		cout.close();
	}
	else {
		MPI_Bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		MPI_Recv(numbers + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		for (int i = start; i < end; ++i) {
			if (sum_digits(numbers[i]) < x) {
				++A;
				answer[i] = numbers[i] * 2;
			}
			else {
				++B;
				answer[i] = numbers[i] / 2;
			}
		}
		MPI_Send(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		MPI_Send(answer + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD);
		if (world_rank != 1) {
			MPI_Send(&A, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
			MPI_Send(&B, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		}
		else {
			int newA, newB;
			for (int i = 2; i < world_size; ++i) {
				MPI_Recv(&newA, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
				MPI_Recv(&newB, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
				A += newA;
				B += newB;
			}
			cout << "A: " << A << '\n';
			cout << "B: " << B << '\n';
		}
	}

	MPI_Finalize();
}