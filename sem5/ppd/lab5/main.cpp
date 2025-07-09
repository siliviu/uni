#include <bits/stdc++.h>
#include "blocking_queue.cpp"

using namespace std;

void pop(blocking_queue<int, -1>& q) {
    cout << q.pop();
}

void push(blocking_queue<int, -1>& q, int val) {
    q.push(val);
}

void test_blocking_queue() {
    blocking_queue<int, -1> q(1);
    thread t[4];
    t[0] = thread(pop, ref(q));
    _sleep(4000);
    t[1] = thread(push, ref(q), 11);
    t[2] = thread(push, ref(q), 22);
    _sleep(1000);
    t[3] = thread(pop, ref(q));

    t[0].join();
    t[1].join();
    t[2].join();
    t[3].join();
}

int main() {
    test_blocking_queue();
}