#include<bits/stdc++.h>
using namespace std;

struct MySingleton{

    static MySingleton &GetInstance(){
        cout << "Getting singleton instance.." << endl;
        static MySingleton _inst;
        return _inst;
    }

    void DoStuff(){
        cout << "Doing stuff.." << endl;
    }

    MySingleton(const MySingleton &s) = delete;
    MySingleton &operator=(const MySingleton &s) = delete;
    MySingleton(const MySingleton &&s) = delete;
    MySingleton &operator=(const MySingleton &&s) = delete;
    
    private:
    MySingleton(){
        cout << "Constructing singleton.." << endl;
    }
};

/*

OUTPUT

Getting singleton instance..
Constructing singleton..
Doing stuff..
Getting singleton instance..
Doing stuff..
Getting singleton instance..
Doing stuff..

*/
int main(){
    MySingleton::GetInstance().DoStuff();
    MySingleton::GetInstance().DoStuff();
    MySingleton::GetInstance().DoStuff();
    return 0;
}