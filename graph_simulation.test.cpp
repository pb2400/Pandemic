#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "graph_simulation.hpp"

// in this test case there will be some tests with 9 people in a grid
TEST_CASE("testing the simulation") {
  // checking the corrent functioning of the program in case
  // beta > 0.5 && gamma < 0.5
  {
    world test(3);
    test.person(0, 0) = people::r_;
    test.person(0, 1) = people::i_;
    test.person(0, 2) = people::r_;
    test.person(1, 0) = people::r_;
    test.person(2, 0) = people::r_;
    test.person(2, 1) = people::r_;
    test.person(2, 2) = people::r_;
    CHECK(neighbours_infected(test, 0, 0) == 0);
    CHECK(neighbours_infected(test, 0, 1) == 0);
    CHECK(neighbours_infected(test, 0, 2) == 0);
    CHECK(neighbours_infected(test, 1, 0) == 0);
    CHECK(neighbours_infected(test, 1, 1) == 1);
    CHECK(neighbours_infected(test, 1, 2) == 1);
    CHECK(neighbours_infected(test, 2, 0) == 0);
    CHECK(neighbours_infected(test, 2, 1) == 0);
    CHECK(neighbours_infected(test, 2, 2) == 0);
    world evolved = successive_stage(test, 0.6, 0.3);
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

  // checking some exceptions in case the values
  // inserted of gamma and beta wouldn't be valid
  {
    world test(3);
    CHECK_THROWS(successive_stage(test, 0.1, 0.2));
  }

  {
    world test(3);
    CHECK_THROWS(successive_stage(test, 1.3, 0.5));
  }

  {
    world test(3);
    CHECK_THROWS(successive_stage(test, 0.6, -2));
  }

  // checking the correct functioning in case of the program in case
  // !(beta > 0.5 && gamma < 0.5)
  {
    world test(3);
    test.person(0, 0) = people::r_;
    test.person(0, 1) = people::i_;
    test.person(0, 2) = people::i_;
    test.person(1, 0) = people::r_;
    test.person(2, 0) = people::r_;
    test.person(2, 1) = people::r_;
    test.person(2, 2) = people::r_;
    CHECK(neighbours_infected(test, 0, 0) == 0);
    CHECK(neighbours_infected(test, 0, 1) == 0);
    CHECK(neighbours_infected(test, 0, 2) == 0);
    CHECK(neighbours_infected(test, 1, 0) == 0);
    CHECK(neighbours_infected(test, 1, 1) == 2);
    CHECK(neighbours_infected(test, 1, 2) == 2);
    CHECK(neighbours_infected(test, 2, 0) == 0);
    CHECK(neighbours_infected(test, 2, 1) == 0);
    CHECK(neighbours_infected(test, 2, 2) == 0);
    world evolved = successive_stage(test, 0.4, 0.3);
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
    test.person(0, 0) = people::r_;
    test.person(0, 1) = people::r_;
    test.person(0, 2) = people::r_;
    test.person(1, 0) = people::r_;
    test.person(2, 0) = people::r_;
    test.person(2, 1) = people::r_;
    test.person(2, 2) = people::r_;
    world evolved = successive_stage(test, 0.6, 0.3);
    CHECK(evolved.person(0, 0) == people::r_);
    CHECK(evolved.person(0, 1) == people::r_);
    CHECK(evolved.person(0, 2) == people::r_);
    CHECK(evolved.person(1, 0) == people::r_);
    CHECK(evolved.person(1, 1) == people::s_);
    CHECK(evolved.person(1, 2) == people::s_);
    CHECK(evolved.person(2, 0) == people::r_);
    CHECK(evolved.person(2, 1) == people::r_);
    CHECK(evolved.person(2, 2) == people::r_);
  }
}