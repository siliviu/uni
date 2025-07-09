#include <bits/stdc++.h>
#include "linked_list.cpp"

using namespace std;
using pi = pair<int, int>;

void test(auto&& function) {
    auto t_start = std::chrono::high_resolution_clock::now();
    function();
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
    std::cout << setprecision(10) << elapsed_time_ms << "\n";
}

int main(int argc, char** argv) {
    int countries = 5, rounds = 10;
    string out = string(argv[1]);
    linked_list<pi> list;
    linked_list<int> disqualified;
    test([&]() {
        for (int i = 0;i < countries;++i) {
            for (int j = 0;j < rounds;++j) {
                ifstream cin(format("data/RezultateC{}_P{}.txt", i + 1, j + 1));
                int id, score;
                while (cin >> id >> score) {
                    if (score == -1) {
                        if (!disqualified.find(id)) {
                            list.remove([&](pi x) {return x.first == id;});
                            disqualified.add_begin(id);
                        }
                    }
                    else if (!disqualified.find(id)) {
                        auto old = list.find([&](pi x) {return x.first == id;});
                        pi val;
                        if (!old)
                            val = { id,score };
                        else {
                            list.remove([&](pi x) {return x.first == id;});
                            val = { id,old->val.second + score };
                        }
                        list.add(val, [&](pi x) {return pair(val.second, val.first) > pair(x.second, x.first);});
                    }
                }
            }
        }
        ofstream cout(out);
        for (auto it = list.root;it;it = it->next)
            cout << it->val.first << ' ' << it->val.second << '\n';
        cout.close();
        }
    );

}