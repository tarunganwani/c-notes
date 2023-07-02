#include <bits/stdc++.h>

using namespace std;


/*

###### async with default launch policy ###### 

-- OUTPUT --
Multiplying... 
Adding.. 
Multiplied output 143
Addition output 24

*/

void async_example1(){

    std::future<int> fut = std::async([](int a,int b){
                                            cout << "Multiplying... " << endl;
                                            this_thread::sleep_for(chrono::milliseconds(2000));
                                            return a*b;
                                        }, 13, 11);
    std::future<int> fut2 = std::async([](int a,int b){
                                            this_thread::sleep_for(chrono::milliseconds(100));
                                            cout << "Adding.. " << endl;
                                            this_thread::sleep_for(chrono::milliseconds(2000));
                                            return a+b;
                                        }, 13, 11);

    int mult = fut.get();
    int add = fut2.get();
    cout << "Multiplied output " <<  mult << endl;
    cout << "Addition output " << add << endl;
}

/*

###### deferred launch policy ###### 

-- OUTPUT --

Adding.. 
Multiplying... 
Multiplied output 120
Addition output 22

*/
void async_example2(){

    std::future<int> fut = std::async(std::launch::deferred, [](int a,int b){
                                            cout << "Multiplying... " << endl;
                                            this_thread::sleep_for(chrono::milliseconds(2000));
                                            return a*b;
                                        }, 10, 12);
    std::future<int> fut2 = std::async(std::launch::async, [](int a,int b){
                                            this_thread::sleep_for(chrono::milliseconds(100));
                                            cout << "Adding.. " << endl;
                                            this_thread::sleep_for(chrono::milliseconds(2000));
                                            return a+b;
                                        }, 10, 12);

    int add = fut2.get();
    int mult = fut.get();
    cout << "Multiplied output " <<  mult << endl;
    cout << "Addition output " << add << endl;
}

/*
###### async with exception ###### 
*/

void async_example3(){
    std::future<void> fut = std::async([](){throw 1;});
    try{
        fut.get();
    } catch(...){
        cout << "Exception caught while getting value from async" << endl;
    }
}

// main
int main(){
    async_example1();
    async_example2();
    async_example3();
    return 0;
}