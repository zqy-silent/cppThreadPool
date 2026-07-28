#pragma once
#include <functional>
#include <memory>
class Task{
private:
  std::shared_ptr<std::function<void()>> func;
public:
  Task() = default;

  //handle lambda or callable
  template<typename F>
  Task(F&& f):func(
    std::make_shared<std::function<void()>>(std::forward<F>(f))) {}  //use share_ptr to prevent copy func

  inline void Execute() const {if(func) (*func)();}
  inline bool IsValid() {return func != nullptr;};
  ~Task() = default;
};


