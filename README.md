# ThreadPool

> A lightweight Thread Pool implemented in Modern C++17 on Linux.

## Overview

This project is a thread pool implemented in **Modern C++17**, redesigned from a Linux C thread pool implementation after studying its source code.

Instead of simply translating C code into C++, the project adopts object-oriented design and encapsulates the system into independent modules such as **Task**, **BlockingQueue**, and **ThreadPool**.

The goal of this project is to understand the design philosophy behind thread pools and practice concurrent programming with Modern C++.

---

Modern C++ ThreadPool

一个基于 C++17 实现的线程池。

Features

Multiple worker threads
Thread-safe blocking queue
mutex + condition_variable synchronization
Generic task submission
std::future asynchronous result
std::packaged_task support
Graceful shutdown
---

## Architecture

```
                 ThreadPool
        +-------------------------+
        | vector<std::thread>     |
        +-------------------------+
                    │
                    ▼
               Worker Threads
                    │
                    ▼
          +---------------------+
          |   BlockingQueue     |
          +---------------------+
          │      mutex          │
          │ condition_variable  │
          ▼                     ▼
              Task Queue
                    │
                    ▼
                 Task
                    │
                    ▼
      std::function<void()>
```

---

## Module Design

### ThreadPool

Responsible for

- Creating worker threads
- Receiving submitted tasks
- Managing thread lifecycle
- Graceful shutdown

Core interfaces

```
ThreadPool(int threadCount);

void Post(std::function<void()> func);

~ThreadPool();

```

---

### BlockingQueue

Responsible for thread-safe task storage.

Main functions

- Push()
- WaitAndPop()
- Close()

Synchronization mechanisms

- std::mutex
- std::condition_variable

---

### Task

Encapsulates executable tasks.

Internally stores

```cpp
std::function<void()>
```

Provides

```cpp
Execute();
```

---

## Synchronization Mechanisms

This project demonstrates three kinds of thread synchronization.

### 1. Mutual Exclusion

Protect shared task queue using

```cpp
std::mutex
```

to prevent data races.

---

### 2. Condition Synchronization

Workers sleep while the queue is empty.

```cpp
cond.wait(...)
```

When a new task arrives,

```cpp
cond.notify_one();
```

wakes up one worker.

---

### 3. Thread Lifecycle Synchronization

When destroying the thread pool,

```cpp
Close();

notify_all();

join();
```

ensures every worker exits gracefully.

---

## Build

### Requirements

- Linux
- g++
- CMake >= 3.10
- C++17

### Build

```bash
mkdir build

cd build

cmake ..

make
```

Run

```bash
./ThreadPoolDemo
```

---

## Example

```cpp
ThreadPool pool(4);

for(int i = 0; i < 10; i++)
{
    pool.Post([i]()
    {
        std::cout
            << "Task "
            << i
            << " running on thread "
            << std::this_thread::get_id()
            << std::endl;
    });
}
```

---

## Project Structure

```
ThreadPool
│
├── include
│   ├── Task.h
│   ├── BlockingQueue.h
│   └── ThreadPool.h
│
├── src
│   ├── Task.cpp
│   ├── BlockingQueue.cpp
│   └── ThreadPool.cpp
│
├── test
│   └── main.cpp
│
├── CMakeLists.txt
└── README.md
```

---

## What I Learned

During this project, I practiced

- Modern C++ object-oriented design
- std::thread
- std::mutex
- std::condition_variable
- Producer-Consumer Model
- RAII
- Blocking Queue
- Thread Synchronization
- Graceful Shutdown
- Linux multi-thread programming
- CMake

---

## Future Improvements

- Support std::future
- Generic template Post()
- Perfect forwarding
- Task priority
- Dynamic thread pool
- Work stealing scheduler

---

## Acknowledgements

This project was redesigned after studying a Linux C thread pool implementation.

The purpose is not to directly translate C code into C++, but to understand the underlying concurrency model and redesign it using Modern C++ practices.
