#include "catch.hpp"

#include "Set.h"

SCENARIO("Using TopologicalSorting") {
    GIVEN("Empty set") {
        Set set(6);
        REQUIRE(set.minVal() == 0);
        REQUIRE(set.maxVal() == 0);
        REQUIRE(set.toString() == "[]");
    }
    GIVEN("One non-empty set") {
        Set set(100);
        set.insert(2);
        set.insert(4);
        set.insert(6);
        set.insert(22);
        set.insert(200);
        set.insert(0);
        REQUIRE(set.minVal() == 2);
        REQUIRE(set.maxVal() == 22);
        REQUIRE(set.toString() == "[2, 4, 6, 22]");
        WHEN("Delete all elements") {
            set.del(2);
            set.del(4);
            set.del(6);
            set.del(22);
            set.del(100);
            THEN("Set is empty") {
                REQUIRE(set.minVal() == 0);
                REQUIRE(set.maxVal() == 0);
                REQUIRE(set.toString() == "[]");
            }
        }
    }
    GIVEN("Set with max and min elem") {
        Set set(95);
        set.insert(1);
        set.insert(95);
        REQUIRE(set.minVal() == 1);
        REQUIRE(set.maxVal() == 95);
        REQUIRE(set.toString() == "[1, 95]");
    }
    GIVEN("Set with elements which are equal to powers of 2") {
        Set set(35);
        set.insert(1);
        set.insert(2);
        set.insert(7);
        set.insert(8);
        set.insert(15);
        set.insert(16);
        set.insert(31);
        set.insert(32);
        REQUIRE(set.maxVal() == 32);
        REQUIRE(set.minVal() == 1);
        REQUIRE(set.toString() == "[1, 2, 7, 8, 15, 16, 31, 32]");
        REQUIRE(set.member(1) == 1);
        REQUIRE(set.member(3) == 0);
        REQUIRE(set.member(7) == 1);
        REQUIRE(set.member(8) == 1);
    }
    GIVEN("Two empty sets") {
        Set a(10);
        Set b(5);
        Set c;
        REQUIRE(c.setUnion(a, b).toString() == "[]");
        REQUIRE(c.intersection(a, b).toString() == "[]");
        REQUIRE(c.difference(a, b).toString() == "[]");
        REQUIRE(c.merge(a, b).toString() == "[]");
        REQUIRE(a.find(b, 3) == 0);
        REQUIRE(a.equal(b) == 1);
    }
    GIVEN("Two non-empty disjoint sets") {
        Set a(100);
        Set b(200);
        a.insert(1);
        a.insert(5);
        a.insert(99);
        b.insert(2);
        b.insert(6);
        b.insert(100);
        Set c;
        REQUIRE(c.setUnion(a, b).toString() == "[1, 2, 5, 6, 99, 100]");
        REQUIRE(c.intersection(a, b).toString() == "[]");
        REQUIRE(c.difference(a, b).toString() == "[1, 5, 99]");
        REQUIRE(c.merge(a, b).toString() == "[1, 2, 5, 6, 99, 100]");
        REQUIRE(a.find(b, 3) == 0);
        REQUIRE(a.find(b, 10) == 0);
        REQUIRE(a.find(b, 1) == &a);
        REQUIRE(a.find(b, 100) == &b);
        REQUIRE(a.equal(b) == 0);
    }
    GIVEN("Two non-disjoint sets") {
        Set a(100);
        Set b(200);
        a.insert(1);
        a.insert(5);
        a.insert(99);
        b.insert(2);
        b.insert(6);
        b.insert(100);
        b.insert(1);
        b.insert(5);
        b.insert(8);
        Set c;
        REQUIRE(c.setUnion(a, b).toString() == "[1, 2, 5, 6, 8, 99, 100]");
        REQUIRE(c.intersection(a, b).toString() == "[1, 5]");
        REQUIRE(c.difference(a, b).toString() == "[99]");
        REQUIRE(c.difference(b, a).toString() == "[2, 6, 8, 100]");
        REQUIRE(c.merge(a, b).toString() == "[1, 2, 5, 6, 8, 99, 100]");
        REQUIRE(a.find(b, 3) == 0);
        REQUIRE(a.find(b, 10) == 0);
        REQUIRE(a.find(b, 1) == &a);
        REQUIRE(a.find(b, 100) == &b);
        REQUIRE(a.equal(b) == 0);
    }
}