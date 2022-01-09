#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <cmath>
#include <cassert>

#include "graph_simulation.hpp"

void print (world const& population)
{
    //command necessary to clean the screen after every day of simulation
    auto const clear = "\033[2J";
    int n = population.side();
    std::cout << clear;

    //building the top of the graph that represent the state of the population
    std::cout << '+' << std::string(n, '-') << "+\n";

    //for needed to build both the left side and right side of the graph
    //while going from left to right with the second for the state of every
    //person that day is analyzed and the function prints and empty char if the person is s_
    //a '*' if the person is infected and a '°' if the person is removed
    //once completed a row the first if allows to switch row, and restart the cycle
    for (int r = 0; r != n; ++r) {
        std::cout << '|';
        for (int c = 0; c != n; ++c) {
            if (population.person(r, c) == people::s_) {
                std::cout << ' ';
            } else {
                if (population.person(r, c) == people::i_) {
                    std::cout << '*';
                } else {
                    std::cout << "°";
                }
            }
        }
        std::cout << "|\n";
    }
    //building the bottom of the graph
    std::cout << '+' << std::string(n, '-') << "+\n";
}

int main()
{
    int number;
    double beta;
    double gamma;
    int s_;
    std::cout << "insert beta's value " << '\n';
    std::cin >> beta;
    std::cout << "insert gamma's value " << '\n';
    std::cin >> gamma;
    std::cout << "choose how many stages of the pandemic simulation you want to see " << '\n';
    std::cin >> s_;
    std::cout <<"choose the number of people you want in the simulation (400 < number < 2500) " << '\n';
    std::cin >> number;

    //the choice of this values for the number of people
    //is linked to graphical reasons: if < 400 the graph is too small
    //if > 2500 the graph is too big
    assert(400 <= number && number <= 2500);
    world population(sqrt(number));

    //building a generator of random numbers
    std::default_random_engine eng{std::random_device{}()};

    //defining the range of numbers that the generator create
    std::uniform_int_distribution<int> dist{0, population.side()};
    
    try {

    //this for is used to assing to 1/25 of the population at day 0 the value of
    //people infected. the people are choosen randomly through the generator created before    
    for (int i = 0; i != population.side() * population.side() / 25; ++i) {
        int r = dist(eng);
        int c = dist(eng);

        //in case the generate would select the same person multiple times
        //this for is needed to regenerate the coordinates of the person we want to 
        //establish as infected
        for (; population.person(r, c) == people::i_; r = dist(eng), c = dist(eng));
        population.person(r, c) = people::i_;
    }
    
    //this for prints the evolutio of the pandemy stage after stage
    //the number of iteration is decided by the user throwgh
    //the number of stages he decides to visualize
    for (int i = 0; i != s_; ++i) {
        population = successive_stage(population, beta, gamma);
        print(population);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }   
    } catch (std::exception const& e) {
        std::cerr << e.what() <<'\n';
        return EXIT_FAILURE;
    } catch (...) {
        std::cerr << "something went wrong" << '\n';
        return EXIT_FAILURE;
    }
 
}