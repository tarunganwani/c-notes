#include <bits/stdc++.h>
#include <shared_mutex>
using namespace std;


// ############### shared mutex ###############
// ############### allows threads to access shared resource without blocking each other
shared_mutex sm;
vector<int> v;

void producer() {
    // ############### shared lock ###############
    std::shared_lock<shared_mutex> sl(sm);
    for(int i = 0; i < 1000; i++){
        cout << "** PRODUCER THREAD [" << this_thread::get_id() << "] value " << i << endl;
        v.push_back(i);
    }
}

void consumer() {
    // ############### shared lock ###############
    shared_lock<shared_mutex> sl(sm);

    for(auto &el: v){
        cout << ">> CONSUMER THREAD [" << this_thread::get_id() << "] value " << el << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {

    thread p(producer);
    p.join();

    // ############### multiple readers ###############
    vector<thread> readerthreads(5);
    for(int i = 0; i < 5; i++){
        readerthreads[i] = thread(consumer);
    }
    for(int i = 0; i < 5; i++){
        readerthreads[i].join();
    }
    
    return 0;
}