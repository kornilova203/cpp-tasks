cmake_minimum_required(VERSION 3.6)
project(queue_with_priorities)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES PriorityQueue.cpp PriorityQueue.h PriorityQueueTest.cpp)
add_executable(queue_with_priorities ${SOURCE_FILES})
INCLUDE_DIRECTORIES("../lib")