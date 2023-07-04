#include <bits/stdc++.h>
using namespace std;

struct Geometry{
    virtual double area() = 0;
    virtual ~Geometry(){};
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

// ****************** FACTORY METHOD ******************

struct GeometryData{
    int w, h;
};

struct GeomFactory{
    virtual Geometry *create_geometry(const GeometryData &) = 0;
};

struct RectFactory : public GeomFactory{
    Geometry *create_geometry(const GeometryData &data)override{
        return new Rectangle(data.w, data.h);
    }
};

struct SquareFactory : public GeomFactory{
    Geometry *create_geometry(const GeometryData &data)override{
        return new Square(data.w);
    }
};

int main(){
    GeometryData d{10, 20};
    GeomFactory *factory = nullptr;
    
    factory = new RectFactory();
    auto rect = factory->create_geometry(d);
    cout << "Rectangle area = " << rect->area() << endl;
    delete rect;
    delete factory;

    factory = new SquareFactory();
    auto sq = factory->create_geometry(d);
    cout << "Square area = " << sq->area() << endl;
    delete sq;
    delete factory;
}