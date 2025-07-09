#include <thread>
#include <mutex>

using namespace std;

template<class T>
struct sync_linked_list {
    mutex mtx;
    struct node {
        T val;
        node* next = 0;
        node() {};
        node(T val) :val(val) {};
    }*root = 0;
    node* find(T _val) { return find([&](T val) {return val == _val;}); }
    node* find(auto&& pred) {
        lock_guard<mutex> lg(mtx);
        node* cur = root;
        while (cur) {
            if (pred(cur->val)) {
                return cur;
            }
            cur = cur->next;
        }
        return 0;
    }
    node* find_and_add(auto&& pred, T val) {
        lock_guard<mutex> lg(mtx);
        if (!root) {
            root = new node(val);
            return 0;
        }
        node* cur = root, * prev = 0;
        while (cur) {
            if (pred(cur->val)) {
                return cur;
            }
            prev = cur;
            cur = cur->next;
        }
        node* newNode = new node(val);
        prev->next = newNode;
        return 0;
    }
    node* find_and_add_update(auto&& pred, T val) {
        lock_guard<mutex> lg(mtx);
        if (!root) {
            root = new node(val);
            return 0;
        }
        node* cur = root, * prev = 0;
        while (cur) {
            if (pred(cur->val)) {
                if (prev)
                    prev->next = cur->next;
                else
                    root = cur->next;
                pair newVal{ val.first,cur->val.second + val.second };
                add_unlocked(newVal, [&](pair<int, int> x) {return pair(newVal.second, newVal.first) > pair(x.second, x.first);});
                return cur;
            }
            prev = cur;
            cur = cur->next;
        }
        node* newNode = new node(val);
        prev->next = newNode;
        return 0;
    }
    bool update(auto&& pred, auto&& pred2) {
        lock_guard<mutex> lg(mtx);
        node* cur = root;
        while (cur) {
            if (pred(cur->val)) {
                cur->val = pred2(cur->val);
                return 1;
            }
            cur = cur->next;
        }
        return 0;
    }
    void add_begin(T val) { add(val, [&](T val) {return true;}); };
    void add_end(T val) { add(val, [&](T val) {return false;}); };

    void add(T val, auto&& cond) {
        lock_guard<mutex> lg(mtx);
        add_unlocked(val, cond);
    }
    void remove(auto&& pred) {
        lock_guard<mutex> lg(mtx);
        remove_unlocked(pred);
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