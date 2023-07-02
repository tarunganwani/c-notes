#include <iostream>
#include <thread>
#include <queue>
#include <cstdlib>
#include <mutex>

//trivial fast producer, slow consumer - with simple mutex

int main(){

    std::queue<int> sharedQ;
    const int QSIZE = 10;
    std::mutex m;

    std::thread producer([&sharedQ, &m, QSIZE](){
        //populate random workload
        for(int i = 0; i < QSIZE; i++){
            auto ms = rand() % QSIZE;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            std::lock_guard<std::mutex> lock(m);
            std::cout  << "[Producer Thread " << std::this_thread::get_id() << "]Pushing payload to sharedQ " << ms << std::endl;
            sharedQ.push(ms);
        }
        for(int i = 0; i < 10; i++)
            sharedQ.push(-1); // End of data
    });

    auto consumerfn = [&sharedQ, &m, QSIZE](){
        while(1){
            int payload;
            bool found = false;
            std::cout << "[Consumer Thread " << std::this_thread::get_id() << "] Looking for work "  << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            {
                std::lock_guard<std::mutex> lock(m);
                if(!sharedQ.empty()){
                    payload = sharedQ.front();
                    sharedQ.pop();
                    found = true;
                }
            }
            if(!found)
                continue;
            if(payload == -1){
                std::cout  << "[Consumer Thread " << std::this_thread::get_id() << "] DONE" << std::endl;
                return;
            }
            std::cout  << "[Consumer Thread " << std::this_thread::get_id() << "] Processing payload " << payload << std::endl;
        }
    };

    std::vector<std::thread *> consumers(2, nullptr);
    for(int i = 0; i < consumers.size(); i++){
        consumers[i] = new std::thread(consumerfn);
    }
    for(int i = 0; i < consumers.size(); i++){
        consumers[i]->join();
    }

    producer.join();
    return 0;
}