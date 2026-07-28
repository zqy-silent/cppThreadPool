#include <queue>
#include <mutex>
#include <condition_variable>
#include "Task.h"
class BlockingQueue {
  private:
    std::mutex threadMutex;
    std::queue<Task> taskQueue;
    std::condition_variable cond;
    bool closed = false;
  private:
    
  public:
    BlockingQueue() = default;
    ~BlockingQueue() = default;
    void Close();

    //accept lambda pased by post()
    template <typename T>
    bool Push(T&& t)
    {
      {
        std::lock_guard<std::mutex> lock(threadMutex);
        if (closed)
          return false;
        taskQueue.emplace(std::forward<T>(t));    //it will call task.consturtor when emplace into queue
      }
      cond.notify_one();
      return true;
    }
    bool WaitAndPop(Task& task);
};