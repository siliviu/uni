#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
 
using namespace std;

class Channel {
public:
    virtual void send(string msg) = 0;        
    virtual ~Channel() = default;
};

class Telefon: public Channel {
    int nrTel;
public:
    Telefon(int _nr) : nrTel{_nr} {}
    void send(string msg) override {
        if(rand() % 100 < 5)
            cout << "Dial: " << nrTel;
        else
            throw runtime_error("BUBA");
    }
};

class Fax : public Telefon {
public:
    Fax(int _nr) : Telefon(_nr) {}
    void send(string msg) override {
        Telefon::send(msg);
        cout << "sending fax";
    }
};

class SMS : public Telefon {
public:
    SMS(int _nr) : Telefon(_nr) {}
    void send(string msg) override {
        Telefon::send(msg);
        cout << "sending sms";
    }
};

class Failover : public Channel {
    Channel* c[2];
public:
    Failover(Channel* c1, Channel* c2) : c{c1,c2} {}
    void send(string msg) override {
        try{
            c[0]->send(msg);
        }
        catch(exception) {
            c[1]->send(msg);
        }
    }
    ~Failover() {
        delete c[0], delete c[1];
    }
};

class Contact {
    Channel* c[3];
public:
    Contact(Channel* c1, Channel* c2, Channel* c3) : c{c1,c2,c3} {}
    ~Contact() {
        delete c[0];
        delete c[1];
        delete c[2];
    }
    void sendAlarm(string msg) {
        while(1) {
            for(int i = 0; i < 3; ++i) {
                try {
                    c[i]->send(msg);
                    return;    
                }
                catch(exception) {
                    cout << "ESUAT";
                }
            }
        }
    }
};

int main() {
    srand(time(0));
    Contact* c = new Contact(new Telefon(12), new Failover(new Fax(10), new SMS(12)), new Failover(new Telefon(12), new Failover(new Fax(10), new SMS(12))));
    c->sendAlarm("Wa");
    delete c;
}
