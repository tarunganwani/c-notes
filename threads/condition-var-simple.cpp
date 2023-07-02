// #include <iostream>
// #include <condition_variable>
// #include <mutex>
// #include <vector>
// #include <thread>
// #include <cstdlib>
#include <bits/stdc++.h>

std::queue<int> shared_queue;
bool shared_ready_flag = false;
int MAXSLEEP = 5;

std::mutex m;
std::condition_variable cv;

void consumer(){

    std::cout << "["<<std::this_thread::get_id()<<"] Consumer waiting.. " << std::endl;
    std::unique_lock<std::mutex> ul(m);
    //consume data
    cv.wait(ul, [](){return shared_ready_flag && !shared_queue.empty();});
    int payload = shared_queue.front();
    std::cout << "["<<std::this_thread::get_id()<<"] consuming payload " << shared_queue.front() << std::endl;
    shared_queue.pop();
    ul.unlock(); //release the lock(explicitly)

    //do morethings with the payloaaaad
    std::this_thread::sleep_for(std::chrono::milliseconds(payload));
    std::cout << "["<<std::this_thread::get_id()<<"] DONE.. " << std::endl;

}

void producer(){    
    std::unique_lock<std::mutex> ul(m);
    std::cout << "["<<std::this_thread::get_id()<<"] Producer - Pushing payload.. " << std::endl;
    shared_queue.push(100);
    shared_queue.push(200);
    shared_ready_flag = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    cv.notify_all();
    std::cout << "["<<std::this_thread::get_id()<<"] Producer - Notified all consumers.. " << std::endl;
}

int main(){
    std::thread cons1(consumer);
    std::thread cons2(consumer);
    std::thread prod(producer);
    std::cout << "["<<std::this_thread::get_id()<<"] MAIN THREAD.. " << std::endl;

    prod.join();
    cons1.join();
    cons2.join();
}