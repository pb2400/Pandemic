#include "graph_simulation.hpp"

#include <stdexcept>

// definition of world constructor
// initializes the member m_with n and initialized the vector m_grid
// in order to create a vector of m_side * m_side full of susceptibles people
world::world(int n) : m_side(n), m_grid(m_side * m_side, people::s_) {}

// definition of method side. Return the value of private member m_side
// useful for some calculation in other methods, free function
// and functions defined in file main-sim.cpp
int world::side() const { return m_side; }

// definition of method person
// since the choice to represent the grid throw a monodimensional index
// this method converts the bi-dimensional index in a monodimensional index
people const &world::person(int r, int c) const {
  auto const i = (r + m_side) % m_side;
  auto const j = (c + m_side) % m_side;
  if (i < 0 || i > m_side || j < 0 || j > m_side) {
    throw std::runtime_error{"unacceptable coordinates"};
  }
  auto const index = i * m_side + j;
  if (index < 0 || index > static_cast<int>(m_grid.size())) {
    throw std::runtime_error{
        "the conversion to monodimensional index went wrong "};
  }
  return m_grid[index];
}

// overloading of method person
// has the same functionality of the other but returns
// a non const reference to people object
people &world::person(int r, int c) {
  auto const i = (r + m_side) % m_side;
  auto const j = (c + m_side) % m_side;

  // checking the values of i and j
  // necessary to calculate the index later
  if (i < 0 || i > m_side || j < 0 || j > m_side) {
    throw std::runtime_error{"unacceptable coordinates"};
  }

  // calculation of monodimensional index
  auto const index = i * m_side + j;

  // checking if the conversion has been successfull
  // obviously the index has to be a value between 0 (we start counting from 0)
  // and the numbers of people in the population
  if (index < 0 || index >= static_cast<int>(m_grid.size())) {
    throw std::runtime_error{
        "the conversion to monodimensional index went wrong "};
  }
  return m_grid[index];
}

// definition of free function neighbours_infected
// its functionality is to count how many adjacent infected people
// an s_ person has
int neighbours_infected(world const &population_, int r, int c) {
  int n_i = 0;

  // the if starts only if the person analyzed is s_
  // otherwhise the infected neighbours aren't counted
  // the first and second for are needed co check every person around him
  // the fact that the person analyzed is counted too doesnt'influence the
  // result because we enter the loop only if the person is susceptible so the
  // counter will not increase the value by one
  if (population_.person(r, c) == people::s_) {
    for (int i : {-1, 0, 1}) {
      for (int j : {-1, 0, 1}) {
        if (population_.person(r + i, c + j) == people::i_) {
          n_i += 1;
        }
      }
    }
    return n_i;
  } else {
    return n_i = 0;
  }
}

// definition of free function successive_stage
// its functionality is to calculate the state of the population
// stage by stage
world successive_stage(world const &present, double beta_, double gamma_) {
  // some if to check if the values of gamma and beta are acceptable
  if (beta_ <= 0 || beta_ >= 1) {
    throw std::runtime_error{"beta's value is not acceptable"};
  }
  if (gamma_ <= 0 || gamma_ >= 1) {
    throw std::runtime_error{"gamma's value is not acceptable"};
  }
  if (beta_ / gamma_ <= 1) {
    throw std::runtime_error{"beta and gamma ratio is unacceptable"};
  }
  int const n = present.side();
  world evolved(n);
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != n; ++j) {
      int a = neighbours_infected(present, i, j);

      // the reason behind this choise is because
      // is because if we follow the formula to calculate the value of the
      // infected stage by stage, the smaller is gamma the bigger the value of
      // infected people will be, and the bigger beta is the bigger will be the
      // value of infected day by day in our code that translates in to a "+1"
      // in to the number of neighbours infected a susceptible person has near
      if (beta_ >= 0.5 && gamma_ <= 0.5) {
        a += 1;
      }

      // the only way inf is greater or equal to 2
      //(based on how the neighbours_infected free function has been
      // implemented) is only if the person analyzed is susceptible. if this
      // happens, the stage after he will be infected otherwise, he will still
      // be susceptible in every other case, in our representation the person
      // will become/stay removed
      int const &inf_ = a;
      if (inf_ >= 2) {
        evolved.person(i, j) = people::i_;
      } else {
        if (present.person(i, j) == people::s_) {
          evolved.person(i, j) = present.person(i, j);
        } else {
          evolved.person(i, j) = people::r_;
        }
      }
    }
  }
  return evolved;
}
