#include <bits/stdc++.h>

void health_checker(){
    int i = 0;
    while(i++ < 500){
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 30));
        std::cout << "Health check.." << std::endl;
    }
    std::cout << "Thread fin. Ctrl+c to exit" << std::endl;
}

int main(){
    std::thread t(health_checker);
    t.detach();

    //do the main work
    std::cout << "do the main work.." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(rand() % 100));

    //DONE
    std::cout << "DONE" << std::endl;
}

