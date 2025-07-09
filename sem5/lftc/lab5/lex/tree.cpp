#include <bits/stdc++.h>

using namespace std;

template<class T>
struct BinaryTree {
    struct node {
        T val;
        int left = -1, right = -1;
        node(T _val) : val(_val) {}
    };
    vector<node> nodes;
    int getSize() {
        return nodes.size();
    }
    node getNode(int number) {
        return nodes[number];
    }
    BinaryTree() {}
    void insert(T val) {
        if (nodes.empty()) {
            nodes.emplace_back(val);
            return;
        }
        int prev = -1, cur = 0;
        while (cur != -1) {
            prev = cur;
            if (val < nodes[cur].val)
                cur = nodes[cur].left;
            else if (val > nodes[cur].val)
                cur = nodes[cur].right;
        }
        if (val < nodes[prev].val)
            nodes[prev].left = nodes.size();
        else
            nodes[prev].right = nodes.size();
        nodes.emplace_back(val);
    }
    int find(T val) {
        if (nodes.empty())
            return -1;
        int cur = 0;
        while (cur != -1) {
            if (val == nodes[cur].val)
                return cur;
            if (val < nodes[cur].val)
                cur = nodes[cur].left;
            else if (val > nodes[cur].val)
                cur = nodes[cur].right;
        }
        return -1;
    }
};

// int main() {
//     BinaryTree<int> bst;
//     bst.insert(8);
//     bst.insert(3);
//     bst.insert(10);
//     bst.insert(1);
//     bst.insert(14);
//     bst.insert(6);
//     bst.insert(4);
//     bst.insert(13);
//     bst.insert(7);
//     // for (int i = 0;i < 9;++i) {
//         // cerr << i << ' ' << bst.getNode(i).val << ' ' << bst.getNode(i).left << ' ' << bst.getNode(i).right << '\n';
//     // }
//     for (int i = 0;i < 10;++i) {
//         int x;
//         cin >> x;
//         cout << bst.find(x) << '\n';
//     }
// }