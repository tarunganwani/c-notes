#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
int main(){

    mutex m;

    // ############ deferred lock ############
    {
        defer_lock_t d;
        unique_lock<mutex> ul(m, d);
        cout << "DEMO - Defered lock type, here lock is not acquired on unique lock creation " << endl;
        cout << "Lock guard doesnt has this flexibility" << endl;
        //...
        ul.lock();
        //critical section
        ul.unlock();
    }
    // // ############ timed lock - C++20 ############
    // {
    //     unique_lock<mutex> ul(m, std::chrono::milliseconds(100));
    //     bool gotlock = false;
    //     gotlock =  ul.try_lock_for(std::chrono::milliseconds(100));
    //     if(gotlock){
    //         cout << "GOT timed lock within 100 ms.." << endl;
    //     } else{
    //         cout << "COULDNT ACQUIRE TIMED LOCK" << endl;
    //     }

    //     // ----------- FAILED LOCK ACQUISITION -----------
    //     auto timedduration = std::chrono::milliseconds(100);
    //     auto delay = std::chrono::milliseconds(200);
    //     unique_lock<mutex> ul2(m, timedduration);
    //     std::this_thread::sleep_for(delay);
    //     gotlock = ul2.try_lock_for(std::chrono::milliseconds(100));
    //     if(gotlock){
    //         cout << "GOT timed lock within 100 ms.." << endl;
    //     } else{
    //         cout << "COULDNT ACQUIRE TIMED LOCK since we werent able to acquire within init timedduration" << endl;
    //     }
    // }


    // ############ scoped lock - lock multiple mutexes ############
    {
        mutex m1, m2;
        {
            std::scoped_lock sl(m1,m2);
            cout << "m1 and m2 are locked using scoped_lock " << endl;
            cout << "try lock on m1 " << boolalpha << m1.try_lock() << endl;
            cout << "try lock on m2 " << boolalpha << m2.try_lock() << endl;
        }
        cout << "m1 and m2 are UNLOCKED due to end of scope" << endl;
        cout << "try lock on m1 " << boolalpha << m1.try_lock() << endl;
        cout << "try lock on m2 " << boolalpha << m2.try_lock() << endl;
        m1.unlock();
        m2.unlock();
    }

}