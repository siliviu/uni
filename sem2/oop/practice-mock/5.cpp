#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
 
using namespace std;

class Participant {
public:
    virtual void tipareste() = 0;
    virtual bool eVoluntar() {
        return true;
    } 
    virtual ~Participant() = default;   
};

class Personal : public Participant {
    string nume;
public:
    Personal(string _nume) : nume(_nume) {}
    void tipareste() override {
        cout << nume;
    }
};

class Director : public Personal {
public:
    Director(string nume) : Personal(nume){}
    void tipareste() override{
        cout << "Director ";
        Personal::tipareste();
    }
};

class Administrator : public Personal {
public:
    Administrator(string nume) : Personal(nume) {}
    void tipareste() override{
        cout << "Administrator ";
        Personal::tipareste();
    }
};

class Angajat : public Participant {
    Participant* p;
public:
    Angajat(Participant* _p) : p(_p) {}
    void tipareste() override {
        cout << "Angajat ";
        p->tipareste();
    }
    bool eVoluntar() override {
        return false;
    }
    ~Angajat() {
        delete p;
    }
};

class ONG {
    vector<Participant*> p;
    public:
    void add(Participant* _p) {
        p.push_back(_p);
    }
    vector<Participant*> getAll(bool vol) {
        vector<Participant*> ans;
        for(auto& x:p)
            if(x->eVoluntar()==vol)
                ans.push_back(x);
        return ans;
    }
    ~ONG() {
        for(auto& x : p)
            delete x;
    }
};
    
int main() {
    ONG* o = new ONG();
    o->add(new Administrator("gabi"));
    o->add(new Angajat(new Administrator("istvan")));
    o->add(new Director("ana"));
    o->add(new Angajat(new Director("gabriela")));
    for(auto& x:o->getAll(false))
        x->tipareste();
    cout << "|";
    for(auto& x:o->getAll(true))
        x->tipareste();        
    delete o;
}
