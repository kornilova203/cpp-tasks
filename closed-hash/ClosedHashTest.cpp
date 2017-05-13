//
// Created by Liudmila Kornilova on 12.05.17.
//


#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "ClosedHash.h"
using namespace std;

TEST_CASE("Check closed hash") {
    ClosedHash<int> closedHash = ClosedHash<int>();

    REQUIRE(closedHash.size() == 0);

    closedHash.insert(1);
    closedHash.insert(11);
    closedHash.insert(2);
    closedHash.insert(2);
    closedHash.insert(22);
    closedHash.insert(13);
    closedHash.insert(23);
    closedHash.insert(23);
    REQUIRE(closedHash.size() == 6);

    REQUIRE(closedHash.member(1) == 1);
    REQUIRE(closedHash.member(11) == 1);
    REQUIRE(closedHash.member(2) == 1);
    REQUIRE(closedHash.member(23) == 1);
    REQUIRE(closedHash.member(32) == 0);
    REQUIRE(closedHash.member(32) == 0);
    REQUIRE(closedHash.member(4) == 0);
    REQUIRE(closedHash.member(22) == 1);

    SECTION("Make Null") {
        closedHash.makeNull();
        REQUIRE(closedHash.size() == 0);
        REQUIRE(closedHash.member(1) == 0);
        REQUIRE(closedHash.member(11) == 0);
        REQUIRE(closedHash.member(2) == 0);
        REQUIRE(closedHash.member(23) == 0);
        REQUIRE(closedHash.member(32) == 0);
        REQUIRE(closedHash.member(32) == 0);
        REQUIRE(closedHash.member(4) == 0);
        REQUIRE(closedHash.member(22) == 0);
    }

    SECTION("deleting elements from hash-table") {
        closedHash.del(1);
        closedHash.del(2);
        closedHash.del(100);
        closedHash.del(99);
        REQUIRE(closedHash.size() == 4);

        REQUIRE(closedHash.member(1) == 0);
        REQUIRE(closedHash.member(2) == 0);
        REQUIRE(closedHash.member(100) == 0);
    }
}

