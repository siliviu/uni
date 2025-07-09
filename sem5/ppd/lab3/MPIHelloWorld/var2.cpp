#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <iomanip>

using namespace std;

int main(int argc, char** argv) {

	MPI_Init(&argc, &argv);

	int world_rank, world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	ifstream cin1("Numar1.txt");
	ifstream cin2("Numar2.txt");
	int N1, N2;
	cin1 >> N1;
	cin2 >> N2;
	int N = max(N1, N2) + 1;
	while (N % world_size)
		++N;
	int chunkSize = N / world_size;
	auto t_start = std::chrono::high_resolution_clock::now();


	unsigned char* s1 = new unsigned char[N];
	unsigned char* s2 = new unsigned char[N];
	unsigned char* s = new unsigned char[N];
	memset(s1, 0, N);
	memset(s2, 0, N);

	MPI_Status status;
	if (world_rank == 0) {
		for (int i = 0; i < N1; ++i) {
			cin1 >> s1[i];
			s1[i] -= '0';
		}
		for (int i = 0; i < N2; ++i) {
			cin2 >> s2[i];
			s2[i] -= '0';
		}
	}

	unsigned char* auxS1 = new unsigned char[chunkSize];
	unsigned char* auxS2 = new unsigned char[chunkSize];
	unsigned char* auxS = new unsigned char[chunkSize];

	MPI_Scatter(s1, chunkSize, MPI_UNSIGNED_CHAR, auxS1, chunkSize, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
	MPI_Scatter(s2, chunkSize, MPI_UNSIGNED_CHAR, auxS2, chunkSize, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

	unsigned char carry = 0;
	for (int i = 0; i < chunkSize; ++i) {
		unsigned char cur = auxS1[i] + auxS2[i] + carry;
		auxS[i] = cur % 10;
		carry = cur / 10;
	}
	unsigned char finalCarry = carry;
	carry = 0;
	if (world_rank != 0)
		MPI_Recv(&carry, 1, MPI_UNSIGNED_CHAR, world_rank - 1, 0, MPI_COMM_WORLD, &status);
	if (carry) {
		for (int i = 0; i < chunkSize && carry; ++i) {
			unsigned char cur = auxS[i] + carry;
			auxS[i] = cur % 10;
			carry = cur / 10;
		}
		if (carry)
			finalCarry = 1;
	}

	if (world_rank + 1 != world_size)
		MPI_Send(&finalCarry, 1, MPI_UNSIGNED_CHAR, world_rank + 1, 0, MPI_COMM_WORLD);
	MPI_Gather(auxS, chunkSize, MPI_UNSIGNED_CHAR, s, chunkSize, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);


	if (world_rank == 0) {
		{
			ofstream cout("Numar3.txt");
			while (N && s[N - 1] == 0)
				--N;
			cout << N << '\n';
			for (int i = 0; i < N; ++i)
				cout << (char)('0' + s[i]);
		}
		auto t_end = std::chrono::high_resolution_clock::now();
		double elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
		cout << setprecision(10) << elapsed_time_ms << '\n';
	}

	MPI_Finalize();
}
