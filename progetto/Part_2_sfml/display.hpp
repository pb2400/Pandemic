#ifndef SIMULATION_DISPLAY_HPP
#define SIMULATION_DISPLAY_HPP

#include "graph_simulation.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

// class display: the description of all its methods
// and their functionalities is in file display.cpp
class display {
private:
  sf::RenderWindow &window;
  sf::Font font;

public:
  // declaration of constructor
  display(sf::RenderWindow &window_);

  // method print
  void print(world const &population) noexcept;

  // method show message
  void show_message(std::string const &message) noexcept;
};

#endif