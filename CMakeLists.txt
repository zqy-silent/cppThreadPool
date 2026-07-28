cmake_minimum_required(VERSION 3.10)

project(ThreadPool)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(ThreadPoolDemo
    src/Task.cpp
    src/BlockingQueue.cpp
    src/ThreadPool.cpp
    test/main.cpp
)

target_link_libraries(ThreadPoolDemo pthread)