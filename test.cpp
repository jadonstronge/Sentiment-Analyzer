//
// Created by jadon on 9/7/2021.
//
#include "catch.hpp"
#include "DSString.h"

TEST_CASE("All DSString functions being tested", "[DSString]") {

    DSString one("My name is Jadon Stronge");
    DSString two("My name is Jadon Stronge");
    DSString three("My name is jadon stronge");
    DSString four("Jadon Stronge is my name");

    SECTION("overloaded assignment operator") {
        DSString test;
        test = one;
        REQUIRE(one == test);
        test = two;
        REQUIRE(two == test);
        REQUIRE(one == two);
    }

    SECTION("overloaded string concatenation") {
        DSString test("!");
        one = one + test;
        two = two + test;
        three = three + test;
        REQUIRE(one == "My name is Jadon Stronge!");
        REQUIRE(two == "My name is Jadon Stronge!");
        REQUIRE(three == "My name is jadon stronge!");
    }

    SECTION("overloaded equality operators") {
        REQUIRE(one == two);
        REQUIRE(!(one == three));
        REQUIRE(!(one == four));
    }

    SECTION("overloaded greater than operator") {
        REQUIRE(three > one);
        REQUIRE(three > four);
        REQUIRE(one > four);
    }

    SECTION("overloaded less than operator") {
        DSString test("a");
        REQUIRE(two < three);
        REQUIRE(four < three);
        REQUIRE(test > three);
    }

    SECTION("overloaded index operator") {
        REQUIRE(one[0] == 'M');
        REQUIRE(three[11] == 'j');
        REQUIRE(four[0] == 'J');
    }

    SECTION("returns string length") {
        DSString test("!");
        REQUIRE(one.length() == 24);
        one = one + test;
        REQUIRE(one.length() == 25);
        REQUIRE(test.length() == 1);
    }

    SECTION("tokenizes string by x amount of chars starting from index") {
        REQUIRE(one.substring(0,1) == "M");
        REQUIRE(one.substring(0,11) == "My name is ");
        REQUIRE(one.substring(11, 1) == "J");
    }

    SECTION("overloaded insertion operator") {
        REQUIRE(std::cout << one << std::endl);
        REQUIRE(std::cout << three << std::endl);
        REQUIRE(std::cout << four << std::endl);
    }

    SECTION("returns index of first occurrence of a char") {
        REQUIRE(one.find('J'));
        REQUIRE(two.find(' '));
        REQUIRE(four.find('i'));
    }

    SECTION("finds first occurrence of substring in char array") {
        DSString test("!");
        REQUIRE(one.find("Jadon"));
        REQUIRE(two.find("Stronge"));
        REQUIRE(!four.find("name!"));
    }
}