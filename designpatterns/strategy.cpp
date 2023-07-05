#include <bits/stdc++.h>
using namespace std;

struct SortStrategy{
    virtual void sort(vector<int> v) = 0;
};

struct QuickSortStrategy : SortStrategy{
    void sort(vector<int> v) override{
        cout << "sorting vector using quick sort" << endl;
    }
};

struct InsertionStrategy : SortStrategy{
    void sort(vector<int> v) override{
        cout << "sorting vector using insertion sort" << endl;
    }
};

struct Context{
    void SetSortStrategy(shared_ptr<SortStrategy> s){
        s_ = s;
    }
    void sortvector(vector<int> &v){
        s_->sort(v);
    }
    private:
        shared_ptr<SortStrategy> s_;
};

int main(){
    vector<int> v {10,20,12,4};
    Context c;
    c.SetSortStrategy(make_shared<QuickSortStrategy>());
    c.sortvector(v);
    c.SetSortStrategy(make_shared<InsertionStrategy>());
    c.sortvector(v);
}