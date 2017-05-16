//
// Created by Liudmila Kornilova on 12.05.17.
//


#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "ClosedHash.h"

using namespace std;

struct S {
    S(const S &s) {
        strcpy(name, s.name);
    }

    S() {
        strcpy(name, "hello");
    }

    S(const char *name_, int n) {
        strcpy(name, name_);
        size = n;
    }

    char *name = new char[15];
    int size = 0;

    int operator==(const S &s) const {
        return strcmp(name, s.name) == 0;
    }
};

namespace std {
    template<>
    class hash<S> {
    public:
        size_t operator()(const S &s) const {
            size_t key = 0;
            for (int i = 0; i < s.size; i++) {
                key += s.name[i];
            }
            return key;
        }
    };
}


SCENARIO("Using hash-table") {
    GIVEN("Hash-table with ints") {

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

        WHEN("Make null") {
            closedHash.makeNull();
            THEN("Size is 0 and no members") {
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
        }

        WHEN("delete elements from hash-table") {
            closedHash.del(1);
            closedHash.del(2);
            closedHash.del(100);
            closedHash.del(99);
            THEN("check size and membership") {
                REQUIRE(closedHash.size() == 4);

                REQUIRE(closedHash.member(1) == 0);
                REQUIRE(closedHash.member(2) == 0);
                REQUIRE(closedHash.member(100) == 0);
            }
        }
    }
    GIVEN("hash-table with struct") {
        ClosedHash<S> closedHash = ClosedHash<S>();
        S s("Lucinda", 7);
        S s2("Lucinda", 7);
        S s3("Misha", 5);
        S s4("Vasya", 5);
        closedHash.insert(s);
        closedHash.insert(s2);
        REQUIRE(closedHash.size() == 1);
        closedHash.insert(s3);
        closedHash.insert(s4);
        REQUIRE(closedHash.size() == 3);
        WHEN("Insert different keys with equal hash") {
            S s5("AB", 2);
            S s6("BA", 2);
            closedHash.insert(s5);
            closedHash.insert(s6);
            THEN("They both are inserted") {
                REQUIRE(closedHash.size() == 5);
            }
        }

    }
}

