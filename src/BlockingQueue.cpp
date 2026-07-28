#include "BlockingQueue.h"

void BlockingQueue::Close()
{
  {
    std::lock_guard<std::mutex> lock(threadMutex);
    closed = true;
  }
  cond.notify_all();
}

bool BlockingQueue::WaitAndPop(Task& task)
{
  //wait part
  std::unique_lock<std::mutex> ulock(threadMutex);
  //1.lock
  cond.wait(ulock,[this](){
    //2.when start sleep, cond unlock
    return !taskQueue.empty() || closed;   //the cond of finishing wait:the queue is not empty or the queue is closed
    //3.when start awake, cond lock for pop part
  });
  //No more tasks and queue has been closed.
  //when had handled all the tasks can tell pool to close
  if(closed && taskQueue.empty())
    return false;
  //pop part
  task = std::move(taskQueue.front());
  taskQueue.pop();
  return true;
}
