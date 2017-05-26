// partially ordered set
// properties:
// Antireflexivity (element does not precede itself
// not(a < a)
// Antisymmetry
// if a < b than not(b < a)
// Transitivity
// if a < b, b < c than a < c

// if all properties are present is set
// means that it is possible to make topological sort

// 3 < 5
// 7 < 3
// 10 < 6
// 6 < 7
// 6 < 5

// 10 -> 6 -> 7 -> 3 -> 5

// list:
// see photo

// value
// amount of predecessors
// pointer to list of next element
// pointer to list of bigger

#include "catch.hpp"

#include "TopologicalSorting.h"

std::string path = "/home/lk/Dropbox/ITMO/programming/cpp-tasks/topological-sorting/test-data/";

SCENARIO("Using TopologicalSorting") {
    GIVEN("Files with correct input") {
        REQUIRE(TopologicalSorting(path + "test1.txt").getSortedOrder() == "3 7 9 5");

        REQUIRE(TopologicalSorting(path + "test2.txt").getSortedOrder() == "1 2 3 5");

        REQUIRE(TopologicalSorting(path + "test3.txt").getSortedOrder() == "1 2 3 4 5 6");

        REQUIRE(TopologicalSorting(path + "test4.txt").getSortedOrder() == "5 6 1 3 2 7 4 9 8");

        REQUIRE(TopologicalSorting(path + "test5.txt").getSortedOrder() == "5 4 2 9 1 10 7 6");

        REQUIRE(TopologicalSorting(path + "test6.txt").getSortedOrder() == "1 2 3 4 5 6 7 8 9");

        REQUIRE(TopologicalSorting(path + "test7.txt").getSortedOrder() == "1 2");

    }
    GIVEN("Files with invalid input") {
        std::string errMessage = "Order was not found";

        REQUIRE(TopologicalSorting(path + "invalid1.txt").getSortedOrder() == errMessage);

        REQUIRE(TopologicalSorting(path + "invalid2.txt").getSortedOrder() == errMessage);

        REQUIRE(TopologicalSorting(path + "invalid3.txt").getSortedOrder() == errMessage);

        REQUIRE(TopologicalSorting(path + "invalid4.txt").getSortedOrder() == errMessage);

    }
}