#include "catch.hpp"

#include "Set.h"

SCENARIO("Using TopologicalSorting") {
    GIVEN("empty set") {
        Set set(6);
        REQUIRE(set.minVal() == 0);
        REQUIRE(set.maxVal() == 0);
    }
}