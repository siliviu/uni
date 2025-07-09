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

void test(auto&& function) {
	auto t_start = std::chrono::high_resolution_clock::now();
	function();
	auto t_end = std::chrono::high_resolution_clock::now();
	double elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
	std::cout << setprecision(10) << elapsed_time_ms << "\n";
}

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	int world_rank, world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	vector<int> sizes(world_size);
	if (world_rank == 0) {
		ifstream cin1("Numar1.txt");
		ifstream cin2("Numar2.txt");
		int N1, N2;
		cin1 >> N1;
		cin2 >> N2;
		int N = max(N1, N2) + 1;
		int P = world_size - 1, block = N / P, remainder = N % P;
		int start = 0, end = block;

		for (int i = 1; i < world_size; ++i) {
			if (remainder) {
				++end;
				--remainder;
			}
			sizes[i] = end - start;
			start = end;
			end = start + block;
		}
	}

	MPI_Bcast(sizes.data(), world_size, MPI_INT, 0, MPI_COMM_WORLD);

	if (world_rank == 0) {
		test([&]() {
			ifstream cin1("Numar1.txt");
			ifstream cin2("Numar2.txt");
			int N1, N2;
			cin1 >> N1;
			cin2 >> N2;
			int N = max(N1, N2) + 1;
			int P = world_size - 1;
			int cur = 0;
			int start = 0;

			for (int i = 1; i < world_size; ++i) {
				int size = sizes[i];
				unsigned char* s1 = new unsigned char[size];
				unsigned char* s2 = new unsigned char[size];

				for (int j = start; j < start + size; ++j) {
					++cur;
					unsigned char c1 = 0, c2 = 0;
					if (cur <= N1) {
						cin1 >> c1;
						c1 -= '0';
					}
					if (cur <= N2) {
						cin2 >> c2;
						c2 -= '0';
					}
					s1[j - start] = c1;
					s2[j - start] = c2;
				}

				MPI_Request requests[2];
				MPI_Isend(s1, size, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD, &requests[0]);
				MPI_Isend(s2, size, MPI_UNSIGNED_CHAR, i, 1, MPI_COMM_WORLD, &requests[1]);

				start += size;
			}

			unsigned char* s = new unsigned char[N + 1];
			int size = 0;
			vector<MPI_Request> recv_requests(world_size - 1);
			vector<int> recv_sizes(world_size - 1);

			for (int i = 1; i < world_size; ++i) {
				recv_sizes[i - 1] = sizes[i];
				MPI_Irecv(s + size, sizes[i], MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD, &recv_requests[i - 1]);
				size += sizes[i];
			}

			MPI_Waitall(world_size - 1, recv_requests.data(), MPI_STATUSES_IGNORE);

			ofstream cout("Numar3.txt");
			while (size && s[size - 1] == 0)
				--size;
			cout << size << '\n';
			for (int i = 0; i < size; ++i)
				cout << (char)('0' + s[i]);

			delete[] s;
			});
	}
	else {
		int size = sizes[world_rank];
		unsigned char* s1 = new unsigned char[size];
		unsigned char* s2 = new unsigned char[size];
		unsigned char* s = new unsigned char[size];

		MPI_Request requests[3];
		MPI_Irecv(s1, size, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD, &requests[0]);
		MPI_Irecv(s2, size, MPI_UNSIGNED_CHAR, 0, 1, MPI_COMM_WORLD, &requests[1]);

		unsigned char carry = 0;
		unsigned char received_carry = 0;
		if (world_rank != 1) {
			MPI_Irecv(&received_carry, 1, MPI_UNSIGNED_CHAR, world_rank - 1, 2, MPI_COMM_WORLD, &requests[2]);
		}
		else {
			requests[2] = MPI_REQUEST_NULL;
		}

		int completed_idx;
		unsigned char finalCarry = 0;
		bool received_s1_flag = false, received_s2_flag = false, received_carry_flag = false;

		for (int i = 0; i < 2; ++i) {
			MPI_Waitany(3, requests, &completed_idx, MPI_STATUS_IGNORE);

			if (completed_idx == 0)
				received_s1_flag = true;
			else if (completed_idx == 1)
				received_s2_flag = true;
			else if (completed_idx == 2)
				received_carry_flag = true;

			if (received_s1_flag && received_s2_flag) {
				for (int i = 0; i < size; ++i) {
					unsigned char cur = s1[i] + s2[i] + carry;
					s[i] = cur % 10;
					carry = cur / 10;
				}
				finalCarry = carry;

				if (!received_carry_flag && world_rank != 1)
					MPI_Wait(&requests[2], MPI_STATUS_IGNORE);

				carry = received_carry;
				for (int i = 0; i < size && carry; ++i) {
					unsigned char cur = s[i] + carry;
					s[i] = cur % 10;
					carry = cur / 10;
				}
				if (carry)
					finalCarry = 1;
				break;
			}

			if (received_carry_flag) {
				carry = received_carry;

				if (!received_s1_flag)
					MPI_Wait(&requests[0], MPI_STATUS_IGNORE);

				if (!received_s2_flag)
					MPI_Wait(&requests[1], MPI_STATUS_IGNORE);

				for (int i = 0; i < size; ++i) {
					unsigned char cur = s[i] + carry;
					s[i] = cur % 10;
					carry = cur / 10;
				}
				finalCarry = carry;
				break;
			}
		}

		if (world_rank + 1 != world_size)
			MPI_Send(&finalCarry, 1, MPI_UNSIGNED_CHAR, world_rank + 1, 2, MPI_COMM_WORLD);

		MPI_Send(s, size, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);

		delete[] s1;
		delete[] s2;
		delete[] s;
	}

	MPI_Finalize();
	return 0;
}
