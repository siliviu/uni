#include <bits/stdc++.h>

template<class T>
struct node {
    T val;
    node* next = 0;
    node(T _val) : val(_val) {};
};

template<class T>
struct list {
    node<T>* root;
    list() {};
    list(const std::vector<T>& elements) {
        root = new node(elements[0]);
        int n = elements.size();
        node<T>* cur = root;
        for (int i = 1;i < n;++i) {
            node<T>* temp = new node(elements[i]);
            cur->next = temp;
            cur = temp;
        }
    }
    static list makeList(T val) {
        list ans;
        ans.root = new node(val);
        return ans;
    }
    void print() {
        for (node<T>* cur = root;cur;cur = cur->next)
            std::cout << cur->val << ' ';
        std::cout << '\n';
    }
    bool isEmpty() {
        return !root;
    }
    friend list operator + (T val, list l) {
        list ans = list::makeList(val);
        ans.root->next = l.root;
        return ans;
    }
    list removeFront() {
        assert(!isEmpty());
        list newlist;
        newlist.root = root->next;
        return newlist;
    }
    T getFront() {
        assert(!isEmpty());
        return root->val;
    }
};

template<class T>
list<T> addEnd(list<T> l, T val) {
    if (l.isEmpty())
        return list<T>::makeList(val);
    return l.getFront() + addEnd(l.removeFront(), val);
}


// template<class T>
// list<T> concat(list<T> a, list<T> b) {
//     if (a.isEmpty() && b.isEmpty())
//         return list<T>();
//     if (a.isEmpty())
//         return b.getFront() + concat(a, b.removeFront());
//     return a.getFront() + concat(a.removeFront(), b);
// }

template<class T>
list<T> concat(list<T> a, list<T> b) {
    if (a.isEmpty())
        return b;
    return a.getFront() + concat(a.removeFront(), b);
}

int main() {
    list<int> a({ 1, 2, 3 });
    a.print();
    list ans = addEnd(a, 4);
    ans.print();

    list<int> b({ 5,6,7 });
    ans = concat(ans, b);
    ans.print();
}