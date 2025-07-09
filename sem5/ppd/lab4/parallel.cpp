#include <bits/stdc++.h>
#include "linked_list.cpp"
#include "blocking_queue.cpp"

using namespace std;
using pi = pair<int, int>;
constexpr pi POISON = { -1,-1 };
mutex mtx;

void test(auto&& function) {
    auto t_start = std::chrono::high_resolution_clock::now();
    function();
    auto t_end = std::chrono::high_resolution_clock::now();
    double elapsed_time_ms = std::chrono::duration<double, std::nano>(t_end - t_start).count();
    std::cout << setprecision(10) << elapsed_time_ms << "\n";
}


void produce(vector<pair<int, int>> files, blocking_queue<pair<int, int>, POISON>& results) {
    for (auto& [i, j] : files) {
        ifstream cin(format("data/RezultateC{}_P{}.txt", i + 1, j + 1));
        int id, score;
        while (cin >> id >> score)
            results.push({ id,score });
    }
}


void consume(blocking_queue<pair<int, int>, POISON>& results, linked_list<pi>& list, linked_list<int>& disqualified, mutex& mtx) {
    while (1) {
        auto [id, score] = results.pop();
        if (id == -1)
            break;
        mtx.lock();
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
        mtx.unlock();
    }
}


int main(int argc, char** argv) {
    int countries = 5, rounds = 10;
    int t_r = stoi(argv[1]);
    int t_w = stoi(argv[2]);
    string out = string(argv[3]);
    linked_list<pi> list;
    linked_list<int> disqualified;
    blocking_queue<pair<int, int>, POISON> results;
    test([&]() {
        vector<thread> tr(t_r), tw(t_w);

        int allRounds = countries * rounds, chunk = allRounds / t_r, start = 0;
        for (int i = 0;i < t_r;++i) {
            int end = start + chunk;
            vector<pair<int, int>> cur;
            for (int j = start;j < end;++j) {
                int country = j / rounds, round = j % rounds;
                cur.emplace_back(country, round);
            }
            tr[i] = thread(produce, cur, ref(results));
            start = end;
        }
        for (auto& x : tw)
            x = thread(consume, ref(results), ref(list), ref(disqualified), ref(mtx));
        for (auto& x : tr)
            x.join();
        results.stop();
        for (auto& x : tw)
            x.join();
        ofstream cout(out);
        for (auto it = list.root;it;it = it->next)
            cout << it->val.first << ' ' << it->val.second << '\n';
        cout.close();
        }
    );

}