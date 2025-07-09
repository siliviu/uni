#include <bits/stdc++.h>
#include "sync_linked_list.cpp"
#include "blocking_queue.cpp"

using namespace std;
using pi = pair<int, int>;
constexpr pi POISON = { -1,-1 };
map<int, mutex> mtxs;
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


void consume(blocking_queue<pair<int, int>, POISON>& results, sync_linked_list<pi>& list, sync_linked_list<int>& disqualified) {
    while (1) {
        auto [id, score] = results.pop();
        if (id == -1)
            break;

        mtx.lock();
        auto& cur = mtxs[id];
        mtx.unlock();

        cur.lock();
        if (score == -1) {
            if (!disqualified.find(id)) {
                list.remove([&](pi x) {return x.first == id;});
                disqualified.add_begin(id);
            }
        }
        else if (!disqualified.find(id)) {
            if (!list.find_and_update([&](pi x) {return x.first == id;}, { id,score }))
                list.add_begin({ id,score });
        }
        cur.unlock();
    }
}


int main(int argc, char** argv) {
    int countries = 5, rounds = 10;
    int t_r = stoi(argv[1]);
    int t_w = stoi(argv[2]);
    int max_cap = stoi(argv[3]);
    string out = string(argv[4]);
    sync_linked_list<pi> list(make_pair(-1, 0));
    sync_linked_list<int> disqualified(-1);
    blocking_queue<pair<int, int>, POISON> results(max_cap);
    test([&]() {
        vector<thread> tr(t_r), tw(t_w);

        int allRounds = countries * rounds, block = allRounds / t_r, remainder = allRounds % t_r;
        int start = 0, end = block;
        for (int i = 0;i < t_r;++i) {
            if (remainder) {
                ++end;
                --remainder;
            }
            vector<pair<int, int>> cur;
            for (int j = start;j < end;++j) {
                int country = j / rounds, round = j % rounds;
                cur.emplace_back(country, round);
            }
            tr[i] = thread(produce, cur, ref(results));
            start = end;
            end = start + block;
        }
        for (auto& x : tw)
            x = thread(consume, ref(results), ref(list), ref(disqualified));
        for (auto& x : tr)
            x.join();
        results.stop();
        for (auto& x : tw)
            x.join();
        ofstream cout(out);
        vector<pi> res;
        for (auto it = list.root;it;it = it->next)
            if (it->val.first >= 0)
                res.emplace_back(it->val);
        sort(res.begin(), res.end(), [&](pi val, pi x) {return pair(val.second, val.first) > pair(x.second, x.first);});
        for (auto& [x, y] : res)
            cout << x << ' ' << y << '\n';
        cout.close();
        }
    );

}