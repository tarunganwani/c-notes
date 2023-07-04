#include <bits/stdc++.h>
using namespace std;


struct BeverageMaker{
    virtual void prepare() {
        boilwater();
        brew();
        pourincup();
        addcondiments();
    }
    void boilwater(){
        cout << "Boiling water.." << endl;
    }
    void pourincup(){
        cout << "Pouring in cup.." << endl;
    }
    virtual void brew() = 0;
    virtual void addcondiments() = 0;
    virtual ~BeverageMaker(){}
};

struct TeaMaker : public BeverageMaker{
    void brew() override {
        cout << "Brewing tea.." << endl;
    }
    void addcondiments() override {
        cout << "Adding lemon.." << endl;
    }

};

struct CoffeeMaker : public BeverageMaker{
    void brew() override {
        cout << "Brewing coffee.." << endl;
    }
    void addcondiments() override {
        cout << "Adding milk and sugar.." << endl;
    }
    
};

int main(){
    unique_ptr<BeverageMaker> teamaker = make_unique<TeaMaker>();
    unique_ptr<BeverageMaker> coffeemaker = make_unique<CoffeeMaker>();
    teamaker->prepare();
    coffeemaker->prepare();
}