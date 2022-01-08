#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "parte2.hpp"

TEST_CASE("testing the simulation")
{
    {   
        world test(3);
        test.person(0, 0) = people::r_;
        test.person(0, 1) = people::i_;
        test.person(0, 2) = people::r_;
        test.person(1, 0) = people::i_;
        test.person(1, 1) = people::s_;
        test.person(1, 2) = people::s_;
        test.person(2, 0) = people::r_;
        test.person(2, 1) = people::r_;
        test.person(2, 2) = people::r_;
        world evolved = day_after(test, 0.6, 0.3);
        CHECK(test.c_t()[0] == people::r_);
        CHECK(neighbours_infected(test, 0, 0) == 2);
        CHECK(neighbours_infected(test, 0, 1) == 1);
        CHECK(neighbours_infected(test, 0, 2) == 2);
        CHECK(neighbours_infected(test, 1, 0) == 1);
        CHECK(neighbours_infected(test, 1, 1) == 2);
        CHECK(neighbours_infected(test, 1, 2) == 2);
        CHECK(neighbours_infected(test, 2, 0) == 2);
        CHECK(neighbours_infected(test, 2, 1) == 2);
        CHECK(neighbours_infected(test, 2, 2) == 2);
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

    {
        world test(3);
        CHECK_THROWS(day_after(test, 0.1, 0.2));
    }

    {
        world test(3);
        CHECK_THROWS(day_after(test, 1.3, 0.5));
    }

    {
        world test(3);
        CHECK_THROWS(day_after(test, 0.6, -2));
    }

    {
        world test(3);
        test.person(0, 0) = people::i_;
        test.person(0, 2) = people::i_;
        test.person(1, 0) = people::r_;
        test.person(1, 1) = people::i_;
        test.person(1, 2) = people::r_;
        test.person(2, 0) = people::r_;
        test.person(2, 1) = people::r_;
        test.person(2, 2) = people::r_;
        world evolved = day_after(test, 0.7, 0.6);
        CHECK(evolved.person(0, 0) == people::r_);
        CHECK(evolved.person(0, 1) == people::i_);
        CHECK(evolved.person(0, 2) == people::r_);
        CHECK(evolved.person(1, 0) == people::r_);
        CHECK(evolved.person(1, 1) == people::r_);
        CHECK(evolved.person(1, 2) == people::r_);
        CHECK(evolved.person(2, 0) == people::r_);
        CHECK(evolved.person(2, 1) == people::r_);
        CHECK(evolved.person(2, 2) == people::r_);
    }

    {
        world test(3);
        test.person(0, 0) = people::i_;
        test.person(0, 2) = people::i_;
        test.person(1, 0) = people::r_;
        test.person(1, 1) = people::r_;
        test.person(1, 2) = people::r_;
        test.person(2, 0) = people::r_;
        test.person(2, 1) = people::r_;
        test.person(2, 2) = people::r_;
        world evolved = day_after(test, 0.7, 0.6);
        CHECK(evolved.person(0, 0) == people::r_);
        CHECK(evolved.person(0, 1) == people::s_);
        CHECK(evolved.person(0, 2) == people::r_);
        CHECK(evolved.person(1, 0) == people::r_);
        CHECK(evolved.person(1, 1) == people::r_);
        CHECK(evolved.person(1, 2) == people::r_);
        CHECK(evolved.person(2, 0) == people::r_);
        CHECK(evolved.person(2, 1) == people::r_);
        CHECK(evolved.person(2, 2) == people::r_);
    }

    {
            world test(3);
        test.person(0, 0) = people::i_;
        test.person(0, 2) = people::i_;
        test.person(1, 0) = people::r_;
        test.person(1, 1) = people::r_;
        test.person(1, 2) = people::r_;
        test.person(2, 0) = people::r_;
        test.person(2, 1) = people::r_;
        test.person(2, 2) = people::r_;
        world evolved = day_after(test, 0.3, 0.2);
        CHECK(evolved.person(0, 0) == people::r_);
        CHECK(evolved.person(0, 1) == people::s_);
        CHECK(evolved.person(0, 2) == people::r_);
        CHECK(evolved.person(1, 0) == people::r_);
        CHECK(evolved.person(1, 1) == people::r_);
        CHECK(evolved.person(1, 2) == people::r_);
        CHECK(evolved.person(2, 0) == people::r_);
        CHECK(evolved.person(2, 1) == people::r_);
        CHECK(evolved.person(2, 2) == people::r_);
    }
}