#include <iostream>
#include <thread>

using namespace std;

void thread_func_no_args(){
    cout << "Hello Thread 1" << endl;
    //do some work
    cout << "End Thread 1" << endl;
}

void thread_func_some_args(int i, double d){
    cout << "Hello Thread Params i = " << i << " d = " << d << endl;
    //do some work
    cout << "End Thread with Params" << endl;
}

int main(){
    cout << "Hello from main" << endl;
    std::thread t1(thread_func_no_args);
    std::thread t2([](){
        cout << "Hello from thread lambda "<< endl;
    });
    std::thread t3(thread_func_some_args, 1, 2);
    std::thread t4([](int i){
        cout << "Hello from thread lambda with params " << i << endl;
    }, 1);

    // cout << "t1 id " << t1.get_id() << endl;
    // cout << "t2 id " << t2.get_id() << endl;
    t2.join();
    t1.join();
    t3.join();
    t4.join();
    cout << "End main" << endl;
}