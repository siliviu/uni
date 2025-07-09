#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Meniu {
    int pret;
public:
    Meniu(int _pret = 0) : pret(_pret) {}
    virtual string descriere() = 0;
    virtual int getPret() {
        return pret;
    }
    virtual ~Meniu() = default;
};

class MicDejun : public Meniu {
    string denumire;
public:
    MicDejun(string _denumire, int pret) : Meniu(pret), denumire(_denumire) {}
    string descriere() override {
        return denumire;
    }
};

class CuCafea : public Meniu {
    Meniu* m;
public:
    CuCafea(Meniu* _m) : m(_m), Meniu(5) {}
    int getPret() override {
        return Meniu::getPret() + m->getPret();
    }
    string descriere() override {
        return m->descriere() + " cu cafea";
    }
    ~CuCafea() {
        delete m;
    }
};

class CuRacoritoare : public Meniu {
    Meniu* m;
public:
    CuRacoritoare(Meniu* _m) : m(_m), Meniu(4) {}
    int getPret() override {
        return Meniu::getPret() + m->getPret();
    }
    string descriere() override {
        return m->descriere() + " cu racoritoarea";
    }
    ~CuRacoritoare() {
        delete m;
    }
};

vector<Meniu*> go () {
    Meniu* Omleta = new MicDejun("OUA", 10);
    cout << Omleta->descriere() << ' ' << Omleta->getPret() << '\n';
    Meniu* OmletaCuCafea = new CuCafea(new MicDejun("OUA", 10));
    cout << OmletaCuCafea->descriere() << ' ' << OmletaCuCafea->getPret() << '\n';
    Meniu* MeniuOmleta = new CuRacoritoare(new CuCafea(new MicDejun("OUA", 10)));
    cout << MeniuOmleta->descriere() << ' ' << MeniuOmleta->getPret() << '\n';
    vector<Meniu*> comanda;
    comanda.push_back(Omleta);
    comanda.push_back(OmletaCuCafea);
    comanda.push_back(MeniuOmleta);
    return comanda;
}

int main() {
    auto v = go();
    sort(v.begin(), v.end(), [&](Meniu* a, Meniu* b){return a->getPret()<b->getPret();});
    for(const auto& x : v) {
        cout << x->descriere() << ' ' << x->getPret() << '\n';
        delete x;
    }
}
