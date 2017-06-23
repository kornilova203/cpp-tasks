cmake_minimum_required(VERSION 3.6)
project(dictionary)

set(CMAKE_CXX_STANDARD 11)
INCLUDE_DIRECTORIES(../lib)

set(SOURCE_FILES OpenHash.h Elem.h tests-main.cpp TESTS.cpp)
add_executable(dictionary ${SOURCE_FILES})