CMAKE_MINIMUM_REQUIRED(VERSION 3.6)
project(topological-sorting)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES TESTS.cpp TopologicalSorting.h Elem.h TESTS.cpp tests-main.cpp)
set(RESOURCE_FILES test1.txt)
add_executable(topological-sorting ${SOURCE_FILES})
INCLUDE_DIRECTORIES(../lib)
