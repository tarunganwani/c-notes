#include<bits/stdc++.h>
using namespace std;


struct Component{
    virtual int Op() = 0;
    virtual ~Component(){}
};

struct LeafElement : public Component {
    LeafElement(int el) : _el(el){}
    int Op() override{
        return _el;
    }
    private:
    int _el;
};

struct AdditionComposite : public Component {
    
    AdditionComposite(){}

    void AddComponent(shared_ptr<Component> c){
        compvector.push_back(c);
    }

    int Op() override{
        int sum = 0;
        for(auto &c : compvector){
            sum += c->Op();
        }
        return sum;
    }

    private:
    vector<shared_ptr<Component>> compvector;
};

int main(){
    shared_ptr<Component> leaf1 = make_shared<LeafElement>(10);
    shared_ptr<Component> leaf2 = make_shared<LeafElement>(20);
    shared_ptr<AdditionComposite> addition1 = make_shared<AdditionComposite>();
    addition1->AddComponent(leaf1);
    addition1->AddComponent(leaf2);

    shared_ptr<Component> leaf3 = make_shared<LeafElement>(100);
    shared_ptr<AdditionComposite> addition2 = make_shared<AdditionComposite>();
    addition2->AddComponent(addition1);
    addition2->AddComponent(leaf3);

    cout << "Leaf1 = " << leaf1->Op() << endl;
    cout << "Leaf2 = " << leaf2->Op() << endl;
    cout << "Addition1 = " << addition1->Op() << endl;
    cout << "Leaf3 = " << leaf3->Op() << endl;
    cout << "Addition2 = " << addition2->Op() << endl;

    return 0;
}