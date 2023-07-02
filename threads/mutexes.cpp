#include <iostream>
#include <mutex>

void recursive_func(std::recursive_mutex &rm, int reccount){
    if(reccount == 0)
        return;
    rm.lock();
    recursive_func(rm, --reccount);
    rm.unlock();
}

int main(){

    {
        // ########### plain mutex #######
        std::mutex m;
        {   
            // ########### explicit lock unlock #######
            m.lock();
            m.unlock();

            // ########### try lock #######
            if(m.try_lock()){
                //.. do critical section stuff
                m.unlock();
            }else{
                std::cout << "mutex try lock acquisition failed" << std::endl;
            }

            // ########### RAII lock  #######
            {
                std::lock_guard<std::mutex> lg(m);
            }
        }



        // ########### recursive mutex #######
        std::recursive_mutex rm;
        int reccount = 5;
        recursive_func(rm, reccount);
        

        // ########### timed mutex #######
        std::timed_mutex tm;
        if(tm.try_lock_for(std::chrono::milliseconds(100))){
            //got lock
            //do critical section stuff
            tm.unlock(); 
        } else{
            std::cout << "timed mutex lock acquisition failed" << std::endl;
        }
    }
    return 0;
}