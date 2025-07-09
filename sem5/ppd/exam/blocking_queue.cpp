#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

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
        // push(POISON);
    }
};