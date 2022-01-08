#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "parte2.hpp"

TEST_CASE("testing the simulation")
{
    {   
        world test(3);
        test.person(0, 1) == people::i_;
        test.person(1, 0) == people::i_;
        test.person(2, 1) == people::r_;
        test.person(0, 0) == people::r_;
        test.person(0, 2) == people::r_;
        test.person(2, 0) == people::r_;
        test.person(2, 2) == people::r_;
        world evolved = day_after(test, 0.6, 0.3);
        CHECK(evolved.person(0, 0) == people::r_);
        CHECK(evolved.person(0, 1) == people::r_);
        CHECK(evolved.person(0, 2) == people::r_);
        CHECK(evolved.person(1, 0) == people::r_);
        CHECK(evolved.person(1, 1) == people::i_);
        CHECK(evolved.person(1, 2) == people::i_);
        CHECK(evolved.person(2, 0) == people::r_);
        CHECK(evolved.person(2, 1) == people::r_);
        CHECK(evolved.person(2, 2) == people::r_);
    }
}