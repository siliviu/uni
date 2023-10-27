#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
 
using namespace std;

class Transformer {
public:
    virtual void transform(vector<int>& v) = 0;
    virtual ~Transformer() = default;
};

class Numbers {
    vector<int> v;
    Transformer* t;    
public:
    Numbers(Transformer* _t) : t(_t) {}
    void add(int nr) {
        v.push_back(nr);
    }
    vector<int> transform() {
        sort(v.begin(), v.end(), greater<int>());
        t->transform(v);
        return v;
    }
    ~Numbers() {
        delete t;
    }
};

class Adder : public Transformer {
    int cat;
public:
    Adder(int _cat) : cat(_cat) {}
    void transform(vector<int>& v) override {
        for (auto& x : v)
            x+=cat;
    }
};

class Nuller : public Adder {
public:
    Nuller(int cat): Adder(cat) {}
    void transform(vector<int>& v) override {
        Adder::transform(v);
        for(auto& x : v)
            if(x > 10)
                x = 0;   
    }
};

class Swapper : public Transformer {
public:
    void transform(vector<int>& v) override {
        int n = v.size();
        for (int i = 1; i < n; i += 2)
            swap(v[i - 1], v[i]);
    }
};

class Composite : public Transformer {
    Transformer* t1, *t2;
public:  
    Composite(Transformer* _t1, Transformer* _t2) : t1(_t1), t2(_t2) {}
    void transform(vector<int>& v) override {
        t1->transform(v);
        t2->transform(v);
    }
    ~Composite() {
        delete t1;
        delete t2;
    }
};

Numbers* go() {
    return new Numbers(new Composite(new Nuller(9), new Composite(new Swapper(), new Adder(3))));
}

int main() {
    auto a=go(), b=go();
    a->add(5), a->add(4), a->add(3), a->add(2), a->add(1);
    b->add(10), b->add(7), b->add(4), b->add(3), b->add(1);
    for (auto& x : a->transform())
        cout << x << ' ';
    cout << '\n';
    for(auto& x: a->transform())
        cout << x << ' ';
    delete a;
    delete b;    
}
