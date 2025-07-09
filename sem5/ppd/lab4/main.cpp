#include <bits/stdc++.h>
#include "linked_list.cpp"
#include "blocking_queue.cpp"

using namespace std;

void test_linked_list() {
    linked_list<int> list;
    list.add_end(4);
    list.add_end(5);
    list.add_end(6);
    list.add_begin(8);
    for (auto cur = list.root; cur;cur = cur->next)
        cout << cur->val << ' ';
    cout << (list.find(4) != 0);
    cout << (list.find([&](int x) {return x == 4;}) != 0);
    cout << (list.find([&](int x) {return x == 7;}) != 0);
    cout << (list.find([&](int x) {return x == 5;}) != 0);
    cout << (list.find([&](int x) {return x == 8;}) != 0);
    cout << (list.find([&](int x) {return x == 9;}) != 0);
    cout << (list.find([&](int x) {return x == 6;}) != 0);
    list.remove([&](int x) {return x == 8;});
    cout << (list.find([&](int x) {return x == 6;}) != 0);
}

void pop(blocking_queue<int, -1>& q) {
    cout << q.pop();
}

void push(blocking_queue<int, -1>& q, int val) {
    q.push(val);
}

void test_blocking_queue() {
    blocking_queue<int, -1> q;
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