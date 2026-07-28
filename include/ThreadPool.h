using namespace std;
#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <future>
#include "BlockingQueue.h"
class ThreadPool {
  private:
    BlockingQueue taskQueue;
    vector<std::thread> workers;
  private:
    void Worker();
  public:
    ThreadPool(int threadCount);
    ~ThreadPool();


    //use universal referance to accept all kinds of func
    template<typename F>
    auto Post(F&& f)
    {
      //get the return type of func
      using returnType = std::invoke_result_t<F>;

      //use shared_ptr to fix ptask cant be copy
      //and easy to be capture cause it is just a pointer
      auto ptask = std::make_shared<std::packaged_task<returnType()>>(
        std::forward<F>(f)
      );

      auto future = ptask->get_future();

      //pase a lambda function which would be called when excute task.Excute()
      if(!taskQueue.Push(
        [ptask]() mutable     
          {
            (*ptask)();    // equal to ptask.operator()(); which means excute operator() but not construtor
          })
        )
      {
        throw std::runtime_error("Post task failed");
      }
      return future;   //return future directly but not the result of future to prevent waitting
    }
};
