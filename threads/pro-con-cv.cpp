#include <iostream>
#include <thread>
#include <queue>
#include <cstdlib>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <functional>

constexpr int NO_OF_CONSUMERS = 5;

struct SharedData{
    std::queue<int> Q;
    std::mutex m;
    std::condition_variable cv;
};

struct Producer{
    Producer(SharedData &d):_data(d){
    }
    void produce_data();
    SharedData &_data;
    static int NUMDATA, BURSTMAX;
};
int Producer::NUMDATA = 10;
int Producer::BURSTMAX = 20;

struct Consumer{
    Consumer(SharedData &d):_data(d){}
    Consumer(SharedData &d, std::string name):_data(d), _name(name){
        std::cout << "Initializing consumer " << name << std::endl;
    }
    void consume_data();
    bool is_data_available(){
        return !_data.Q.empty();
    }
    SharedData &_data;
    std::string _name;
};


void Producer::produce_data(){

    for(int i = 0; i < NUMDATA; i++){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::lock_guard<std::mutex> lock(this->_data.m);
        for(int b = 0; b < BURSTMAX; b++){
            auto payload = rand() % Producer::NUMDATA;
            this->_data.Q.push(payload);
            std::cout << "[" << std::this_thread::get_id() << "] Producer Thread :: Payload " << payload << std::endl;
        }
        this->_data.cv.notify_all();
    } //lock is released
    std::lock_guard<std::mutex> lock(this->_data.m);
    for(int i = 0; i < NO_OF_CONSUMERS; i++){
        std::cout << "[" << std::this_thread::get_id() << "] Producer Thread :: END OF PAYLOAD(-1) " << std::endl;
        this->_data.Q.push(-1);
    }  //lock is released
}

void Consumer::consume_data(){
    while(1){
        std::unique_lock<std::mutex> ulock(this->_data.m);
        // this->_data.cv.wait(lock, std::bind(Consumer::is_data_available, this));
        this->_data.cv.wait(ulock, [this](){
            return !this->_data.Q.empty();
        });
        //consume the data
        int payload = this->_data.Q.front();
        this->_data.Q.pop();
        ulock.unlock();

        std::cout << "[" << std::this_thread::get_id() << "] Consumer Thread " << this->_name << " :: " << payload << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(payload/2));
        if(payload == -1){
            std::cout << "[" << std::this_thread::get_id() << "] Consumer Thread " << this->_name << " :: DONE " << std::endl;
            return;
        }
    }
}


int main(){

    SharedData sd;
    std::vector<Consumer *> consvec(NO_OF_CONSUMERS, nullptr);
    std::vector<std::thread *> consvecthreads(NO_OF_CONSUMERS, nullptr);
    for(int i = 0; i < NO_OF_CONSUMERS; i++){
        std::cout << "Initializing consumer.." << std::endl;
        auto ptr = new Consumer(sd, std::string("CONSUMER")+std::to_string(i));
        consvec[i] = ptr;
        std::cout << "Spawning consumer thread.." << std::endl;
        consvecthreads[i] = new std::thread(&Consumer::consume_data, consvec[i]);
    }

    std::cout << "Spawning producer thread.." << std::endl;
    Producer p(sd);
    std::thread prothread(&Producer::produce_data, &p);
    prothread.join();
    for(int i = 0; i < NO_OF_CONSUMERS; i++){
        consvecthreads[i]->join();
        delete consvec[i];
        consvec[i] = nullptr;
    }
    
    // std::thread producer()
}