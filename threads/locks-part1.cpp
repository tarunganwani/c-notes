#include <thread>
#include <mutex>
#include <iostream>

int main(){

    std::mutex m;

    // ############ LOCK GUARD ############ 
    {
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        std::cout << "lock guard DOES NOT has the FLEXIBILITY to be manually released/acquired " << std::endl;
        std::lock_guard<std::mutex> lg(m);
        //lg.unlock(); // -> error, lock guard can not be manually locked or unlocked
        std::cout << std::endl;
        //NOTE: lock_guard is LESS FLEXIBLE
    }

    // ############ UNIQUE LOCK ############ 
    {
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        std::cout << "unique lock has the FLEXIBILITY to be manually released/acquired " << std::endl;
        std::cout << std::endl;
        
        std::unique_lock<std::mutex> ul(m);
        
        std::cout << "unique lock allows OWNERSHIP transfer to move the mutex to a diff lock" << std::endl;
        std::cout << "moving lock to ul2.." << std::endl;
        std::unique_lock<std::mutex> ul2(std::move(ul));
        std::cout << "Check if ul still owns the lock " << std::boolalpha << ul.owns_lock() << std::endl;
        std::cout << "Check if ul2 owns the lock " << std::boolalpha << ul2.owns_lock() << std::endl;
        
        std::cout << std::endl;
        std::cout << "manually unlocking mutex using ul2.." << std::endl;
        ul2.unlock();
        std::cout << "Check if ul2 still owns the lock " << std::boolalpha << ul2.owns_lock() << std::endl;
        
    }

    // ############ TRY LOCK ############ 
    {
        std::mutex m1, m2;
        std::cout << "-------------------------------------------------------------------------" << std::endl;
        // try_lock tries to acquire locks multiple mutexes

        bool gotlock = std::try_lock(m1, m2);
        std::cout << "Check we got the lock using try_lock " << std::boolalpha << gotlock << std::endl;
        if(gotlock){
            std::cout << "Yay, we acquired the locks. \n\trelease them now..! " << std::endl;
            //do some work
            m1.unlock();
            m2.unlock();            
        } else{
            std::cout << "Failed to acquire locks.." << std::endl;
        }

        m1.lock();
    }

    return 0;
}