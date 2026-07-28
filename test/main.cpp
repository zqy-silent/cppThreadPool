#include "ThreadPool.h"
#include <iostream>
#include <chrono>
#include <thread>


int main()
{
    {
        ThreadPool pool(4);

        for(int i=0;i<10;i++)
        {
            pool.Post([i](){

                std::cout 
                    << "running task "
                    << i
                    << std::endl;

                std::this_thread::sleep_for(
                    std::chrono::seconds(1)
                );

            });
        }

    } //?¨½àD?ªRÌÛ


    std::cout<<"pool destroyed"<<std::endl;

    return 0;
}