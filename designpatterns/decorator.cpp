#include <bits/stdc++.h>
using namespace std;

struct Coffee{
    virtual double cost() = 0;
    virtual string description() = 0;
    virtual ~Coffee() {}
};

struct Latte : public Coffee{
    double cost() override{
        return 200; //Rupees
    }
    string description(){
        return "Latte";
    }
};

struct Decaf : public Coffee{
    double cost() override{
        return 250; //Rupees
    }
    string description(){
        return "Decaf";
    }
};

struct CondimentDecorator : public Coffee{
};

struct ChocolateDecorator : public CondimentDecorator{
    ChocolateDecorator(Coffee *coffeeObj){
        _coffeeObj = coffeeObj;
    }
    double cost() override{
        return 50 + _coffeeObj->cost(); //Rupees
    }
    string description(){
        return _coffeeObj->description() + ", with chocolate";
    }
    Coffee *_coffeeObj;
};

struct CardamomDecorator : public CondimentDecorator{
    CardamomDecorator(Coffee *coffeeObj){
        _coffeeObj = coffeeObj;
    }
    double cost() override{
        return 10 + _coffeeObj->cost(); //Rupees
    }
    string description(){
        return _coffeeObj->description() + ", with cardamom";
    }
    Coffee *_coffeeObj;
};

int main(){
    Coffee *decaf = new Decaf();
    CondimentDecorator *decafPlusChocolate = new ChocolateDecorator(decaf);
    CondimentDecorator *order1 = new CardamomDecorator(decafPlusChocolate);
    cout << "Coffee desc : " << order1->description() << endl;
    cout << "Coffee cost : " << order1->cost() << endl;
    delete decaf;
    delete order1;
}