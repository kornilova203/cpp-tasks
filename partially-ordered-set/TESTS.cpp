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

#include "PartiallyOrderedSet.h"

std::string path = "/home/lk/Dropbox/ITMO/programming/cpp-tasks/partially-ordered-set/";

SCENARIO("Using PartiallyOrderedSet") {
    GIVEN("Files with correct input") {
        REQUIRE(PartiallyOrderedSet(path + "test1.txt").getOrder() == "3 5 7 9");

        REQUIRE(PartiallyOrderedSet(path + "test2.txt").getOrder() == "3 2 1 5");

        REQUIRE(PartiallyOrderedSet(path + "test3.txt").getOrder() == "1 2 3 4 5 6");

        REQUIRE(PartiallyOrderedSet(path + "test4.txt").getOrder() == "4 1 8 2 3 5 6 7 9");

        REQUIRE(PartiallyOrderedSet(path + "test5.txt").getOrder() == "1 7 2 4 9 5 6 10");

        REQUIRE(PartiallyOrderedSet(path + "test6.txt").getOrder() == "1 2 3 4 5 6 7 8 9");

        REQUIRE(PartiallyOrderedSet(path + "test7.txt").getOrder() == "1 2");

    }
    GIVEN("Files with invalid input") {
        std::string errMessage = "Order was not found";

        REQUIRE(PartiallyOrderedSet(path + "invalid1.txt").getOrder() == errMessage);

        REQUIRE(PartiallyOrderedSet(path + "invalid2.txt").getOrder() == errMessage);

        REQUIRE(PartiallyOrderedSet(path + "invalid3.txt").getOrder() == errMessage);

        REQUIRE(PartiallyOrderedSet(path + "invalid4.txt").getOrder() == errMessage);

    }
}