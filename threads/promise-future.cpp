#include <bits/stdc++.h>
using namespace std;

void some_thread_fn(std::promise<int> &prom, int exceptionflag){
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cout << "Starting worker thread.." << endl;
    if(exceptionflag){
        try{
            throw std::runtime_error("some runtime exception occured");
        } catch(...){
            prom.set_exception(std::current_exception());
        }
        return;
    }
    //else
    prom.set_value(1);
}

int main(){

    std::promise<int> prom, prom1;
    std::future<int> fut = prom.get_future();
    std::future<int> fut1 = prom1.get_future();


    std::thread some_thread(some_thread_fn, std::ref(prom), 0);

    cout << "MAIN THREAD blocked until promise is fulfilled, ie value is ready.." << endl;
    int ret = fut.get();
    cout << "GOT return value :: ret = " << ret << endl;
    some_thread.join();


    std::thread some_thread1(some_thread_fn, std::ref(prom1), 1/*EXCEPTION FLAG*/);
    cout << "MAIN THREAD blocked until promise is fulfilled, ie value/exception is ready.." << endl;
    try{
        ret = fut1.get();
    }catch(std::exception &e){
        cout << "GOT exception :: exception = " << e.what() << endl;
    }
    some_thread1.join();

    return 0;
}