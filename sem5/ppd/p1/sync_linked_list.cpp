#include <thread>
#include <mutex>

using namespace std;

template<class T>
struct sync_linked_list {

    struct node {
        T val;
        mutex mtx;
        node* next = 0;
        node() {};
        node(T val) : val(val) {};
    }*root = 0;

    sync_linked_list(T start) {
        root = new node(start);
    }

    node* find(T _val) { return find([&](T val) {return val == _val;}); }
    node* find(auto&& pred) {
        node* cur = root;
        while (cur) {
            cur->mtx.lock();
            if (pred(cur->val)) {
                cur->mtx.unlock();
                return cur;
            }
            cur->mtx.unlock();
            cur = cur->next;
        }
        return 0;
    }
    node* find_and_update(auto&& pred, T val) {
        node* cur = root;
        while (cur) {
            cur->mtx.lock();
            if (pred(cur->val)) {
                cur->val[2] += val[2];
                cur->mtx.unlock();
                return cur;
            }
            cur->mtx.unlock();
            cur = cur->next;
        }
        return 0;
    }
    void add_begin(T val) {
        root->mtx.lock();
        node* newNode = new node(val);
        newNode->next = root->next;
        root->next = newNode;
        root->mtx.unlock();
    };
    void remove(auto&& pred) {
        node* cur = root->next, * prev = root;
        prev->mtx.lock();
        while (cur) {
            cur->mtx.lock();
            if (pred(cur->val)) {
                prev->next = cur->next;
                cur->mtx.unlock();
                prev->mtx.unlock();
                return;
            }
            prev->mtx.unlock();
            prev = cur;
            cur = cur->next;
        }
        prev->mtx.unlock();
    }
private:
    void remove_unlocked(auto&& pred) {
        node* cur = root, * prev = 0;
        while (cur) {
            if (pred(cur->val)) {
                if (prev)
                    prev->next = cur->next;
                else
                    root = cur->next;
                return;
            }
            prev = cur;
            cur = cur->next;
        }
    }
    void add_unlocked(T val, auto&& cond) {
        node* cur = root, * prev = 0;
        if (!root) {
            root = new node(val);
            return;
        }
        while (cur && !cond(cur->val)) {
            prev = cur;
            cur = cur->next;
        }
        node* newNode = new node(val);
        newNode->next = cur;
        if (!prev)
            root = newNode;
        else
            prev->next = newNode;
    }
};