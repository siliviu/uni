#include <bits/stdc++.h>
#include <vector>
#include <thread>
#include <cassert>
#include <chrono>

using namespace std;

int generateRandomNumber(int upperBoundary) {
    return rand() % upperBoundary + 1;
}

void printArray(const vector<int>& a, int n) {
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";
}

int operation(int a, int b) {
    // return a + b;
    return sqrt(a * a * a * a * sin(a) + log(b * b));
}
const int N = 50'000'000, UPBOUND = 100'000'000, P = 16;

void task(vector<int>& a, vector<int>& b, int start, int end, vector<int>& c) {
    for (int i = start;i < end;++i)
        c[i] = operation(a[i], b[i]);
}

template<class T>
void test(string name, T function) {
    auto t_start = std::chrono::high_resolution_clock::now();
    function();
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << name << ": " << elapsed_time_ms << "\n";
}

int main() {
    srand(time(0));
    vector<int> a(N), b(N);

    for (int i = 0;i < N;++i) {
        a[i] = generateRandomNumber(UPBOUND);
        b[i] = generateRandomNumber(UPBOUND);
    }

    vector<int> cSerial(N);
    test("serial", [&]() {
        task(a, b, 0, N, cSerial);
        });

    vector<int> cParallel(N);
    test("parallel (" + to_string(P) + " threads)", [&]() {
        vector<thread> threads(P);
        int block = N / P, remainder = N % P;
        int start = 0, end = block;
        for (int i = 0;i < P;++i) {
            if (remainder) {
                ++end;
                --remainder;
            }
            threads[i] = thread(task, ref(a), ref(b), start, end, ref(cParallel));
            start = end;
            end = start + block;
        }

        for (auto& x : threads)
            x.join();
        }
    );

    assert(cSerial == cParallel);
}