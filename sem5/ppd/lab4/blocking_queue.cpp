#include <thread>
#include <mutex>
#include <semaphore>
#include <queue>

using namespace std;

template<class T, T POISON, int MAX_CAPACITY = 100'000'000>
struct blocking_queue {
    queue<T> q;
    mutex mtx;
    counting_semaphore<MAX_CAPACITY> sem_add{ 0 };
    counting_semaphore<MAX_CAPACITY> sem_remove{ MAX_CAPACITY };
    void push(T val) {
        sem_remove.acquire();
        mtx.lock();
        q.push(val);
        mtx.unlock();
        sem_add.release();
    }
    T pop() {
        sem_add.acquire();
        mtx.lock();
        T val = q.front();
        if (val == POISON)
            sem_add.release();
        else
            q.pop();
        mtx.unlock();
        sem_remove.release();
        return val;
    }
    void stop() {
        push(POISON);
    }
};