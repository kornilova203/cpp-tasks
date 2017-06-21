cmake_minimum_required(VERSION 3.6)
project(set_on_bit_field)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES Set.h TESTS.cpp tests-main.cpp)
add_executable(set_on_bit_field ${SOURCE_FILES})
INCLUDE_DIRECTORIES(../lib)