#include <bits/stdc++.h>
using namespace std;

struct Geometry{
    virtual double area() = 0;
};

struct Rectangle : public Geometry{
    Rectangle(int w,int h):_w(w), _h(h){}
    virtual double area() override{
        return _w*_h;
    }
    int _w,_h;
};

struct Square : public Geometry{
    Square(int s):_s(s){}
    virtual double area() override{
        return _s*_s;
    }
    int _s;
};
// ****************** SIMPLE FCTORY ******************
unique_ptr<Geometry> GetShape(int choice, int w, int h = 0){
    switch(choice){
        case 1:
            return make_unique<Rectangle>(w,h);
        case 2:
            return  make_unique<Square>(w);
    }
    return nullptr;
}

int main(){
    auto sq = GetShape(2, 200);
    auto rect = GetShape(1, 200, 100);
    cout << "Square area = " << sq->area() << endl;
    cout << "Rectangle area = " << rect->area() << endl;
}