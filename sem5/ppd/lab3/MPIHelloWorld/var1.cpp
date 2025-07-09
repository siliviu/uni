#include <mpi.h>
#include <bits/stdc++.h>

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

    MPI_Status status;
    if (world_rank == 0) {
        test([&]() {

            ifstream cin1("Numar1.txt");
            ifstream cin2("Numar2.txt");
            int N1, N2;
            cin1 >> N1;
            cin2 >> N2;
            int N = max(N1, N2);
            int P = world_size - 1, block = N / P, remainder = N % P;
            int start = 0, end = block, cur = 0;
            for (int i = 1; i < world_size; ++i) {
                if (remainder) {
                    ++end;
                    --remainder;
                }
                int size = end - start;
                unsigned char* s1 = new unsigned char[size];
                unsigned char* s2 = new unsigned char[size];
                for (int j = start; j < end; ++j) {
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
                MPI_Send(&size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                MPI_Send(s1, size, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD);
                MPI_Send(s2, size, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD);
                start = end, end = start + block;
            }
            unsigned char* s = new unsigned char[N + 1];
            int size = 0;
            for (int i = 1; i < world_size; ++i) {
                int cursize;
                MPI_Recv(&cursize, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
                MPI_Recv(s + size, cursize, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD, &status);
                size += cursize;
            }
            ofstream cout("Numar3.txt");
            cout << size << '\n';
            for (int i = 0; i < size; ++i)
                cout << (char)('0' + s[i]);
            });
    }
    else {
        int size;
        MPI_Recv(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        unsigned char* s1 = new unsigned char[size];
        unsigned char* s2 = new unsigned char[size];
        unsigned char* s = new unsigned char[size + 1];
        MPI_Recv(s1, size, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(s2, size, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        unsigned char carry = 0;
        for (int i = 0; i < size; ++i) {
            unsigned char cur = s1[i] + s2[i] + carry;
            s[i] = cur % 10;
            carry = cur / 10;
        }
        unsigned char finalCarry = carry;
        carry = 0;
        if (world_rank != 1)
            MPI_Recv(&carry, 1, MPI_UNSIGNED_CHAR, world_rank - 1, 0, MPI_COMM_WORLD, &status);
        if (carry) {
            for (int i = 0; i < size && carry; ++i) {
                unsigned char cur = s[i] + carry;
                s[i] = cur % 10;
                carry = cur / 10;
            }
            if (carry)
                finalCarry = 1;
        }
        if (world_rank + 1 != world_size)
            MPI_Send(&finalCarry, 1, MPI_UNSIGNED_CHAR, world_rank + 1, 0, MPI_COMM_WORLD);
        else if (finalCarry)
            s[size++] = 1;
        MPI_Send(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(s, size, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}
