#include <bits/stdc++.h>
using namespace std;

struct MyThreadSafeSingleton{

    static MyThreadSafeSingleton *GetInstance(){
        if(_inst == nullptr){
            lock_guard<mutex> lg(m);
            if(_inst == nullptr){
                _inst = new MyThreadSafeSingleton();
            }
        }
        cout << "Thread " << this_thread::get_id() << " - Getting singleton instance.." << endl;
        return _inst;
    }

    void SomeOperation(){
        cout << "Thread " << this_thread::get_id() << " - Some Operation.." << endl;
    }
    MyThreadSafeSingleton(const MyThreadSafeSingleton &) = delete;
    MyThreadSafeSingleton &operator=(const MyThreadSafeSingleton &) = delete;
    MyThreadSafeSingleton(const MyThreadSafeSingleton &&) = delete;
    void operator=(const MyThreadSafeSingleton &&) = delete;

    private:
    MyThreadSafeSingleton(){
        cout <<"Constructing singleton.." << endl;
    }
    static MyThreadSafeSingleton *_inst;
    static mutex m;
};
MyThreadSafeSingleton *MyThreadSafeSingleton::_inst = nullptr;
mutex MyThreadSafeSingleton::m;


void threadfn(){
    for(int i = 0; i < 100; i++){
        this_thread::sleep_for(chrono::milliseconds(rand()%50));
        auto inst = MyThreadSafeSingleton::GetInstance();
        inst->SomeOperation();
        MyThreadSafeSingleton::GetInstance()->SomeOperation();
    }
}
int main() {
    thread t1(threadfn);
    thread t2(threadfn);
    thread t3(threadfn);
    thread t4(threadfn);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}