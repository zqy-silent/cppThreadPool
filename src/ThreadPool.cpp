#include "ThreadPool.h"

ThreadPool::ThreadPool(int threadCount){
  for(int i=0; i<threadCount; i++){
    workers.emplace_back(&ThreadPool::Worker, this);          
  }
}

ThreadPool::~ThreadPool(){
  taskQueue.Close();
  for(auto& t: workers){
    t.join();
  }
}

void ThreadPool::Worker(){
  while(true){
    Task task;
    if(!taskQueue.WaitAndPop(task))
      break;
    //excute func of task
    if(task.IsValid())
      task.Execute();   //excute ptask.operator()
  }
}