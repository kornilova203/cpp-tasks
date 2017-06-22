#include "catch.hpp"

#include "Set_ul.h"

SCENARIO("Testing set on unordered list") {
    GIVEN("Empty set") {
        Set_ul set;
        REQUIRE(set.minVal() == 0);
        REQUIRE(set.maxVal() == 0);
        REQUIRE(set.toString() == "[]");
    }
    GIVEN("One non-empty set") {
        Set_ul set;
        set.insert(2);
        set.insert(4);
        set.insert(6);
        set.insert(22);
        set.insert(200);
        set.insert(0);
        REQUIRE(set.minVal() == 0);
        REQUIRE(set.maxVal() == 200);
        REQUIRE(set.toString() == "[2, 4, 6, 22, 200, 0]");
        WHEN("Delete all elements") {
            set.del(2);
            set.del(4);
            set.del(6);
            set.del(22);
            set.del(100);
            set.del(200);
            set.del(0);
            THEN("Set_ul is empty") {
                REQUIRE(set.minVal() == 0);
                REQUIRE(set.maxVal() == 0);
                REQUIRE(set.toString() == "[]");
            }
        }
    }
    GIVEN("Set_ul with max and min elem") {
        Set_ul set;
        set.insert(1);
        set.insert(95);
        REQUIRE(set.minVal() == 1);
        REQUIRE(set.maxVal() == 95);
        REQUIRE(set.toString() == "[1, 95]");
    }
    GIVEN("Set_ul with elements which are equal to powers of 2") {
        Set_ul set;
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
        Set_ul a;
        Set_ul b;
        Set_ul c;
        REQUIRE(c.setUnion(a, b).toString() == "[]");
        REQUIRE(c.intersection(a, b).toString() == "[]");
        REQUIRE(c.difference(a, b).toString() == "[]");
        REQUIRE(c.merge(a, b).toString() == "[]");
        REQUIRE(a.find(b, 3) == 0);
        REQUIRE(a.equal(b) == 1);
    }
    GIVEN("Two non-empty disjoint sets") {
        Set_ul a;
        Set_ul b;
        a.insert(1);
        a.insert(5);
        a.insert(99);
        b.insert(2);
        b.insert(6);
        b.insert(100);
        Set_ul c;
        REQUIRE(c.setUnion(a, b).toString() == "[1, 5, 99, 2, 6, 100]");
        REQUIRE(c.intersection(a, b).toString() == "[]");
        REQUIRE(c.difference(a, b).toString() == "[99, 5, 1]");
        REQUIRE(c.merge(a, b).toString() == "[1, 5, 99, 2, 6, 100]");
        REQUIRE(a.find(b, 3) == 0);
        REQUIRE(a.find(b, 10) == 0);
        REQUIRE(a.find(b, 1) == &a);
        REQUIRE(a.find(b, 100) == &b);
        REQUIRE(a.equal(b) == 0);
    }
    GIVEN("Two non-disjoint sets") {
        Set_ul a;
        Set_ul b;
        a.insert(1);
        a.insert(5);
        a.insert(99);
        b.insert(2);
        b.insert(6);
        b.insert(100);
        b.insert(1);
        b.insert(5);
        b.insert(8);
        Set_ul c;
        REQUIRE(c.setUnion(a, b).toString() == "[1, 5, 99, 2, 6, 100, 8]");
        REQUIRE(c.intersection(a, b).toString() == "[5, 1]");
        REQUIRE(c.difference(a, b).toString() == "[99]");
        REQUIRE(c.difference(b, a).toString() == "[8, 100, 6, 2]");
        REQUIRE(c.merge(a, b).toString() == "[]");
        REQUIRE(a.find(b, 3) == 0);
        REQUIRE(a.find(b, 10) == 0);
        REQUIRE(a.find(b, 1) == &a);
        REQUIRE(a.find(b, 100) == &b);
        REQUIRE(a.equal(b) == 0);
    }
}