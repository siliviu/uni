#include <bits/stdc++.h>

using namespace std;

void test(auto&& function) {
    auto t_start = std::chrono::high_resolution_clock::now();
    function();
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
    std::cout << setprecision(10) << elapsed_time_ms << "\n";
}

int main() {
    test([&]() {

        int N1, N2;
        ifstream cin1("Numar1.txt");
        cin1 >> N1;
        string s1;
        cin1 >> s1;
        for (auto& x : s1)
            x -= '0';
        ifstream cin2("Numar2.txt");
        cin2 >> N2;
        string s2;
        cin2 >> s2;
        for (auto& x : s2)
            x -= '0';
        int N = max(N1, N2);
        s1.resize(N), s2.resize(N);
        string ans(N, 0);
        unsigned char carry = 0;
        for (int i = 0;i < N;++i) {
            unsigned char cur = s1[i] + s2[i] + carry;
            ans[i] = cur % 10;
            carry = cur / 10;
        }
        if (carry) {
            ans.push_back(1);
            ++N;
        }
        ofstream cout("Numar3.txt");
        cout << N << '\n';
        for (auto& x : ans)
            x += '0';
        cout << ans;
        cout.close();

        });
}