#include "display.hpp"
#include "graph_simulation.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <random>
#include <thread>

int main() {
  try {

    // IMPORTANT: the choice of letting the user insert the value of people on
    // the side of the window (int side) will lead to a non perfect
    // representation of population in the window. for some values of people
    // inserted, two sides of the window will remain white but don't represent
    // the population, is just due to conversions and approximations of numbers
    // during calculations. value suggested = 40
    int side;
    double beta;
    double gamma;
    std::cout << "insert the number of people that will be on the side of the "
                 "graph (suggested 40) "
              << '\n';
    std::cin >> side;
    std::cout << "insert beta's value " << '\n';
    std::cin >> beta;
    std::cout << "insert gamma's value " << '\n';
    std::cin >> gamma;
    assert(side > 0);
    auto const window_title{"pandemic simulation"};
    sf::RenderWindow window{sf::VideoMode(640, 640), window_title,
                            sf::Style::Default};

    // this option is enabled to avoid some artifact during the simulation
    window.setVerticalSyncEnabled(true);

    display display{window};

    world population(side);

    {
      std::default_random_engine eng{std::random_device{}()};
      std::uniform_int_distribution<int> dist{0, population.side() - 1};

      for (int i = 0; i != side * side / 25; ++i) {
        auto r = dist(eng);
        auto c = dist(eng);
        for (; population.person(r, c) == people::i_;
             r = dist(eng), c = dist(eng))
          ;
        population.person(r, c) = people::i_;
      }
    }

    if (window.isOpen()) {

      // setting window(and susceptibles) color
      window.clear(sf::Color::White);
      display.print(population);
      display.show_message("Press any key to start/stop ");
      window.display();

      sf::Event event;
      while (window.waitEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
          break;
        } else if (event.type == sf::Event::Closed) {
          window.close();
        }
      }
    }

    // boolean value useful to start/stop/restart the simulation
    bool running = true;

    // while cicle to define operations while window is opened
    while (window.isOpen()) {
      sf::Event event;

      // if any key is pressed the simulation temporarily stops
      // while if the close button is pressed the window will close
      while (window.pollEvent(event)) {
        if (event.type == sf::Event::KeyPressed) {
          running = !running;
        } else if (event.type == sf::Event::Closed) {
          window.close();
        }
      }

      // clears the windows after evert stage
      window.clear(sf::Color::White);

      // prints the population state stage after stage
      if (running) {
        population = successive_stage(population, beta, gamma);
        display.print(population);
        window.display();
      }
    }
  } catch (std::exception const &e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "caught unknown exception\n";
    return EXIT_FAILURE;
  }
}
