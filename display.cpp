#include "display.hpp"

// definition of constructor
display::display(sf::RenderWindow &window_) : window{window_} {
  if (!font.loadFromFile("arial.ttf")) {
    throw std::runtime_error{"cannot load font "};
  }
}

// definition of method print: its functionality is to print
// on the window the state of the population during the pandemic
void display::print(world const &population) noexcept {
  int const n = population.side();

  // vector 2f is the type to initialize a rectangle shape
  // vector2f is sf::vector2<float>, a type made by two floats
  // when used in rectangle shape tells the size of the sides of the geometric
  // figure the choosen size is the size of the window divided by the number of
  // people per side
  sf::Vector2f const person_size{window.getSize() / static_cast<unsigned>(n)};

  // creating and setting rettangle shape displayed on window
  // a single rectangle (square in this case)
  // represents a person in the population
  // two squares have been created. the first one represents the removed people
  // the color assigned is green
  // the second one represents the infected people
  // the color assigned is red
  sf::RectangleShape removed(person_size);
  removed.setFillColor(sf::Color::Green);
  removed.setOutlineThickness(1.f);
  removed.setOutlineColor(sf::Color::Black);

  sf::RectangleShape infected(person_size);
  infected.setFillColor(sf::Color::Red);
  infected.setOutlineThickness(1.f);
  infected.setOutlineColor(sf::Color::Yellow);

  // cicle for to check the state of the population in the day of pandemic
  // the method setposition allows to slide throw the grid of people
  // and draw a rectangle for every position but susceptibles'
  // whose rectangle will be created "automatically" by printing the others
  // susceptible rectangle will be white (window color)
  for (int r = 0; r != n; ++r)
    for (int c = 0; c != n; ++c) {
      if (population.person(r, c) == people::r_) {
        removed.setPosition(r * person_size.y, c * person_size.x);
        window.draw(removed);
      } else if (population.person(r, c) == people::i_) {
        infected.setPosition(r * person_size.y, c * person_size.x);
        window.draw(infected);
      }
    }
}

// method display, used in main to print a message on the window
void display::show_message(std::string const &message) noexcept {
  sf::Text text{message, font};
  text.move((window.getSize().x - text.getLocalBounds().width) / 2,
            window.getSize().y / 4);
  text.setFillColor(sf::Color::Black);

  window.draw(text);
}