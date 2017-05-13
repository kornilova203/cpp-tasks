cmake_minimum_required(VERSION 3.6)
project(dictionary)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ClosedHash.h ClosedHashTest.cpp)
add_executable(dictionary ${SOURCE_FILES})
INCLUDE_DIRECTORIES("/home/lk/cpp-resources/")