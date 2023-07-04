#include <bits/stdc++.h>
using namespace std;

struct Observer{
    virtual void update(int) = 0;
};

struct TempWebObserver : public Observer{
    void update(int tempdata) override{
        cout << "TempWebObserver " << tempdata << endl;
    }
};

struct HeatAdjustingDeviceObserver : public Observer{
    void update(int tempdata) override{
        cout << "HeatAdjustingDeviceObserver " << tempdata << endl;
    }
};

// struct
struct Subject{
    virtual void addObserver(Observer *o) = 0;
    virtual void notify() = 0;
    virtual void setstate(int data) = 0;
};

struct Temperature : public Subject{

    virtual void addObserver(Observer *o) override{
        _observerVec.push_back(o);
    }

    void notify() override{
        for_each(_observerVec.begin(),_observerVec.end(),[this](Observer *o){
            o->update(this->temp);
        });
    }

    void setstate(int data) override{
        temp = data;
        notify();
    }
    vector<Observer *> _observerVec;
    int temp;
};

int main(){
    unique_ptr<Subject> temperature = make_unique<Temperature>();
    unique_ptr<Observer> webobsvr = make_unique<TempWebObserver>();
    unique_ptr<Observer> heatadjobsvr = make_unique<HeatAdjustingDeviceObserver>();

    temperature->addObserver(webobsvr.get());
    temperature->addObserver(heatadjobsvr.get());

    temperature->setstate(100);

    return 0;
}