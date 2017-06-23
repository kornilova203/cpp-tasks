#include <fstream>
#include "catch.hpp"
#include "OpenHash.h"

std::string path = "/home/lk/Dropbox/ITMO/programming/cpp-tasks/open-hash/test-data/";

SCENARIO("Using hashTable") {
    GIVEN("File with one name") {
        OpenHash hash(path + "01-one-name.txt");
        REQUIRE(hash.toString() == "Sato\n");
        REQUIRE(hash.member("Sato") == 1);
        REQUIRE(hash.member("Lucinda") == 0);
        WHEN("Delete this one name") {
            hash.del("Sato");
            hash.del("Lucinda");
            THEN("HashTable is empty") {
                REQUIRE(hash.toString() == "");
                REQUIRE(hash.member("Sato") == 0);
                REQUIRE(hash.member("Lucinda") == 0);
            }
        }
    }
    GIVEN("File with one repeated name") {
        OpenHash hash(path + "02-one-repeated-name.txt");
        REQUIRE(hash.toString() == "Sato\n");
        REQUIRE(hash.member("Sato") == 1);
        REQUIRE(hash.member("Lucinda") == 0);
        WHEN("Delete this one name") {
            hash.del("Sato");
            hash.del("Lucinda");
            THEN("HashTable is empty") {
                REQUIRE(hash.toString() == "");
                REQUIRE(hash.member("Sato") == 0);
                REQUIRE(hash.member("Lucinda") == 0);
            }
        }
    }
    GIVEN("File with multiple names") {
        OpenHash hash(path + "03-multiple-names.txt");
        REQUIRE(hash.toString() == "Takahashi\n"
                "Ito\n"
                "Suzuki\n"
                "Hayashi\n"
                "Tanaka\n"
                "Watanabe\n"
                "Shimizu\n"
                "Sato\n"
                "Kimura\n");
        REQUIRE(hash.member("Sato") == 1);
        REQUIRE(hash.member("Tanaka") == 1);
        REQUIRE(hash.member("Hayashi") == 1);
        REQUIRE(hash.member("Lucinda") == 0);
        WHEN("Delete one name") {
            hash.del("Sato");
            hash.del("Lucinda");
            THEN("One name is deleted") {
                REQUIRE(hash.toString() == "Takahashi\n"
                        "Ito\n"
                        "Suzuki\n"
                        "Hayashi\n"
                        "Tanaka\n"
                        "Watanabe\n"
                        "Shimizu\n"
                        "Kimura\n"
                );
                REQUIRE(hash.member("Sato") == 0);
                REQUIRE(hash.member("Tanaka") == 1);
                REQUIRE(hash.member("Hayashi") == 1);
            }
        }
    }
}