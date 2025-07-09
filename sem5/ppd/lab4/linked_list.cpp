template<class T>
struct linked_list {
    struct node {
        T val;
        node* next = 0;
        node() {};
        node(T val) :val(val) {};
    }*root = 0;
    node* find(T _val) { return find([&](T val) {return val == _val;}); }
    node* find(auto&& pred) {
        node* cur = root;
        while (cur) {
            if (pred(cur->val))
                return cur;
            cur = cur->next;
        }
        return 0;
    }
    bool update(auto&& pred, auto&& pred2) {
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
    void remove(auto&& pred) {
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
};