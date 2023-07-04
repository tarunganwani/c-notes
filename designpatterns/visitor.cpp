#include<bits/stdc++.h>
using namespace std;

struct Shapes;
struct Polygon;
struct Rectangle;

struct Visitor{
    virtual void VisitPolygon(Polygon *p) = 0;
    virtual void VisitRectangle(Rectangle *r) = 0;
};

struct LoggingVisitor : public Visitor{
    void VisitPolygon(Polygon *p) override{
        cout << "Logging Rectangle " << endl;
    }
    void VisitRectangle(Rectangle *r) override{
        cout << "Logging Rectangle " << endl;
    }
};

struct DrawingVisitor : public Visitor{
    void VisitPolygon(Polygon *p) override{
        cout << "Drawing Polygon " << endl;
    }
    void VisitRectangle(Rectangle *r) override{
        cout << "Drawing Rectangle " << endl;
    }
};

struct Shapes{
    virtual void accept(Visitor *v) = 0;
};

struct Polygon : public Shapes{
    virtual void accept(Visitor *v) override{
        v->VisitPolygon(this);
    }
};

struct Rectangle : public Shapes{
    virtual void accept(Visitor *v) override{
        v->VisitRectangle(this);
    }
};

int main(){
    unique_ptr<Shapes> rect = make_unique<Rectangle>();
    unique_ptr<Shapes> poly = make_unique<Polygon>();
    unique_ptr<Visitor> logging = make_unique<LoggingVisitor>();
    unique_ptr<Visitor> drawing = make_unique<DrawingVisitor>();

    poly->accept(logging.get());
    rect->accept(logging.get());
    poly->accept(drawing.get());
    rect->accept(drawing.get());

    return 0;
}