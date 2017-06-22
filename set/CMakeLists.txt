cmake_minimum_required(VERSION 3.6)
project(set_on_bit_field)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        bit-field/Set_bits.h
        linked-unordered-list/Set_ul.h
        bit-field/TESTS.cpp
        linked-unordered-list/TESTS.cpp
        tests-main.cpp
        linked-ordered-list/Set_ol.h
        linked-unordered-list/Elem.h)
add_executable(set_on_bit_field ${SOURCE_FILES})
INCLUDE_DIRECTORIES(../lib)