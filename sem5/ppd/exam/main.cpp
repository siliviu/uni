#include <bits/stdc++.h>

using namespace std;

int ORDERS = 90, CAP_MAX = 30;
int O = 3, No = 10, To = 15;
int CHUNK = ORDERS / O;
int L = 4, Tl = 10;
int Tm = 40;

using pi = pair<int, int>;
constexpr pi POISON{ -1,-1 };
bool doneProducing = false, done = false;
mutex mtx;
condition_variable anyNotEmpty;
map<int, vector<int>> orders;

template<class T, T POISON>
struct blocking_queue {
    blocking_queue(int maxCapacity) : maxCapacity(maxCapacity) {}
    queue<T> q;
    mutex mtx;
    int size = 0;
    int maxCapacity;
    condition_variable notEmpty, notFull;
    int getSize() {
        mtx.lock();
        int nr = size;
        mtx.unlock();
        return nr;
    }
    void push(T val) {
        unique_lock<mutex> lock(mtx);
        notFull.wait(lock, [this] { return (int)q.size() < maxCapacity;});
        q.push(val);
        ++size;
        lock.unlock();
        notEmpty.notify_one();
        anyNotEmpty.notify_one();
    }
    T pop() {
        unique_lock<mutex> lock(mtx);
        notEmpty.wait(lock, [this] { return !q.empty();});
        T val = q.front();
        if (val == POISON) {
            lock.unlock();
            notEmpty.notify_one();
        }
        else {
            q.pop();
            --size;
            lock.unlock();
            notFull.notify_one();
        }
        return val;
    }
    void stop() {
        push(POISON);
    }
};

blocking_queue<pi, POISON> q1(30), q2(30);

vector<thread> t_P(O), t_C(L);
std::barrier sync_point_p(std::ssize(t_P), [] {
    q1.stop();
    q2.stop();
    doneProducing = true;
    // cerr << "STOPPED1\n";
    });
std::barrier sync_point_w(std::ssize(t_C), [] {
    done = true;
    // cerr << "STOPPED2\n";
    });

int generateRandomNumber(int lowerBound, int upperBound) {
    return rand() % (upperBound - lowerBound) + lowerBound;
}

int generateRandomNumber(int upperBound) {
    return rand() % upperBound;
}

string generateRandomString(int length) {
    string ans = "";
    while (length--) {
        ans += (char)('a' + generateRandomNumber(26));
    }
    return ans;
}

void generate() {
    ofstream ccout("input.txt");
    for (int i = 0;i < ORDERS;++i)
        ccout << i << ' ' << generateRandomNumber(1, 3) << endl;
    ccout.close();
}

void produce(int nr) {
    ifstream cin("input.txt");
    int start = nr * CHUNK;
    int dummy;
    for (int i = 0;i < start;++i)
        cin >> dummy >> dummy;
    for (int i = 0;i < CHUNK;) {
        int id_order, priority;
        for (int j = 0;j < No;++j, ++i) {
            cin >> id_order >> priority;
            // cout << format("{} {}\n", id_order, nr);
            // cerr << id_order << priority << '\n';
            if (priority == 1)
                q1.push({ nr, id_order });
            else
                q2.push({ nr, id_order });
        }
        this_thread::sleep_for(chrono::milliseconds(To));
    }
    sync_point_p.arrive();
}


void consume() {
    bool done = false;
    while (1) {
        unique_lock<mutex> lock(mtx);
        anyNotEmpty.wait(lock, [&] {return q1.getSize() != 0 || q2.getSize() != 0;});
        lock.unlock();
        auto [id_operator, id_order] = ((q1.getSize() != 0 && !done) ? q1.pop() : q2.pop());
        if (doneProducing && id_operator == -1) {
            if (!done)
                done = true;
            else
                break;
        }
        if (id_operator == -1)
            continue;
        mtx.lock();
        orders[id_operator].push_back(id_order);
        mtx.unlock();
        this_thread::sleep_for(chrono::milliseconds(Tl));
    }
    sync_point_w.arrive();
}

//  g++-13 -std=c++23 -pthread main.cpp -o main


int main(int argc, char** argv) {
    generate();
    for (int i = 0;i < O;++i) {
        t_P[i] = thread(produce, i);
    }
    for (int i = 0;i < L;++i) {
        t_C[i] = thread(consume);
    }
    while (!done) {
        std::time_t result = std::time(nullptr);
        std::cout << std::asctime(std::localtime(&result)) << ' ' << "Q1: " << q1.getSize() << ' ' << "Q2: " << q2.getSize() << '\n';
        this_thread::sleep_for(chrono::milliseconds(Tm));
    }

    for (auto& x : t_P)
        x.join();
    for (auto& x : t_C)
        x.join();

    ofstream cout("output.txt");
    for (auto [id, v] : orders) {
        cout << id << ": ";
        for (auto x : v)
            cout << x << ' ';
        cout << '\n';
    }
}