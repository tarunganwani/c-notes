#include <bits/stdc++.h>
using namespace std;

struct Ticket{
    string issue_;
};

struct SupportHandler{
    virtual void SetNextHandler(SupportHandler *h) = 0;
    virtual ~SupportHandler(){}
    virtual void HandleTicket(Ticket &) = 0;
};

struct BasicSupportHandler : public SupportHandler{
    void SetNextHandler(SupportHandler *h) override{
        next = h;
    }
    void HandleTicket(Ticket &t) override{
        if(t.issue_ == "escalated" && next != nullptr){
            cout << "Ticket is escalated type and CAN NOT BE attended by basic support operator" << endl;
            cout << "Handing off to escalated handler" << endl;
            next->HandleTicket(t);
            return;
        }
        //else
        cout << "Ticket being attended by basic support operator" << endl;
    }
    private:
        SupportHandler *next;
};


struct EscalatedSupportHandler : public SupportHandler{
    void SetNextHandler(SupportHandler *h) override{
        next = h;
    }
    void HandleTicket(Ticket &t) override{
        cout << "Ticket being attended by escalated support operator" << endl;
    }
    private:
        SupportHandler *next;
};


int main(){
    Ticket ticket1{"basic"};
    Ticket ticket2{"escalated"};
    unique_ptr<SupportHandler> esh = make_unique<EscalatedSupportHandler>();
    unique_ptr<SupportHandler> bsh = make_unique<BasicSupportHandler>();
    bsh->SetNextHandler(esh.get());
    bsh->HandleTicket(ticket1);
    bsh->HandleTicket(ticket2);
    return 0;
}