#include <iostream>
#include <iomanip>
#include <cassert>
#include <chrono>
#include <utility>
#include <cuda_runtime.h>

constexpr int TILE_WIDTH = 10;
constexpr int BLOCK_SIZE = 10;
constexpr float EPS = 1e-2;

// https://alvinwan.com/how-to-tile-matrix-multiplication/

__global__ void matrixMultiplyTiled(float* d_A, float* d_B, float* d_C, int N) {
    __shared__ float tile_A[TILE_WIDTH][TILE_WIDTH];
    __shared__ float tile_B[TILE_WIDTH][TILE_WIDTH];

    int row = blockIdx.y * TILE_WIDTH + threadIdx.y;
    int col = blockIdx.x * TILE_WIDTH + threadIdx.x;
    float value = 0;

    for (int k = 0; k < (N + TILE_WIDTH - 1) / TILE_WIDTH; k++) {
        if (row < N && k * TILE_WIDTH + threadIdx.x < N)
            tile_A[threadIdx.y][threadIdx.x] = d_A[row * N + k * TILE_WIDTH + threadIdx.x];
        else
            tile_A[threadIdx.y][threadIdx.x] = 0;

        if (col < N && k * TILE_WIDTH + threadIdx.y < N)
            tile_B[threadIdx.y][threadIdx.x] = d_B[(k * TILE_WIDTH + threadIdx.y) * N + col];
        else
            tile_B[threadIdx.y][threadIdx.x] = 0;

        __syncthreads();

        for (int i = 0; i < TILE_WIDTH; i++)
            value += tile_A[threadIdx.y][i] * tile_B[i][threadIdx.x];

        __syncthreads();
    }

    if (row < N && col < N)
        d_C[row * N + col] = value;
}

__global__ void matrixMultiply(float* d_A, float* d_B, float* d_C, int N) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < N && col < N) {
        float value = 0;

        for (int k = 0; k < N; ++k) {
            value += d_A[row * N + k] * d_B[k * N + col];
        }

        d_C[row * N + col] = value;
    }
}


void matrixMultiplyCUDATiled(float* h_A, float* h_B, float* h_C, int N) {
    size_t bytes = N * N * sizeof(float);

    float* d_A, * d_B, * d_C;
    cudaMalloc(&d_A, bytes);
    cudaMalloc(&d_B, bytes);
    cudaMalloc(&d_C, bytes);

    cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice);

    dim3 dimBlock(TILE_WIDTH, TILE_WIDTH, 1);
    dim3 dimGrid((N + TILE_WIDTH - 1) / TILE_WIDTH, (N + TILE_WIDTH - 1) / TILE_WIDTH, 1);

    matrixMultiplyTiled << <dimGrid, dimBlock >> > (d_A, d_B, d_C, N);

    cudaMemcpy(h_C, d_C, bytes, cudaMemcpyDeviceToHost);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}

void matrixMultiplyCUDA(float* h_A, float* h_B, float* h_C, int N) {
    size_t bytes = N * N * sizeof(float);

    float* d_A, * d_B, * d_C;
    cudaMalloc(&d_A, bytes);
    cudaMalloc(&d_B, bytes);
    cudaMalloc(&d_C, bytes);

    cudaMemcpy(d_A, h_A, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_B, h_B, bytes, cudaMemcpyHostToDevice);


    dim3 blockDim(BLOCK_SIZE, BLOCK_SIZE);
    dim3 gridDim((N + blockDim.x - 1) / blockDim.x, (N + blockDim.y - 1) / blockDim.y);

    matrixMultiply << <gridDim, blockDim >> > (d_A, d_B, d_C, N);

    cudaMemcpy(h_C, d_C, bytes, cudaMemcpyDeviceToHost);

    cudaFree(d_A);
    cudaFree(d_B);
    cudaFree(d_C);
}


void matrixMultiplyCPU(float* h_A, float* h_B, float* h_C, int N) {
    for (int i = 0;i < N;++i)
        for (int j = 0;j < N;++j) {
            float res = 0;
            for (int k = 0;k < N;++k)
                res += h_A[i * N + k] * h_B[k * N + j];
            h_C[i * N + j] = res;
        }
}

int main(int argc, char** argv) {
    assert(argc == 2);
    int N = atoi(argv[1]);

    float* h_A = new float[N * N];
    float* h_B = new float[N * N];
    float* h_C1 = new float[N * N];
    float* h_C2 = new float[N * N];
    float* h_C0 = new float[N * N];

    for (int i = 0; i < N * N; i++) {
        h_A[i] = static_cast<float>(rand()) / RAND_MAX;
        h_B[i] = static_cast<float>(rand()) / RAND_MAX;
    }

    auto t_start = std::chrono::high_resolution_clock::now();
    matrixMultiplyCUDA(h_A, h_B, h_C1, N);
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
    std::cout << "CUDA" << std::endl;
    std::cout << std::setprecision(10) << elapsed_time_ms << "\n";

    t_start = std::chrono::high_resolution_clock::now();
    matrixMultiplyCUDATiled(h_A, h_B, h_C2, N);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
    std::cout << "CUDA Optimised" << std::endl;
    std::cout << std::setprecision(10) << elapsed_time_ms << "\n";

    t_start = std::chrono::high_resolution_clock::now();
    matrixMultiplyCPU(h_A, h_B, h_C0, N);
    t_end = std::chrono::high_resolution_clock::now();
    elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
    std::cout << "CPU" << std::endl;
    std::cout << std::setprecision(10) << elapsed_time_ms << "\n";

    for (int i = 0;i < N * N;++i)
        assert(abs(h_C0[i] - h_C1[i]) <= EPS);

    for (int i = 0;i < N * N;++i)
        assert(abs(h_C0[i] - h_C2[i]) <= EPS);

    delete[] h_A;
    delete[] h_B;
    delete[] h_C0;
    delete[] h_C1;
    delete[] h_C2;
}
