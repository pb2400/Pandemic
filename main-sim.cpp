#include <iostream>
#include <chrono>
#include <random>
#include <thread>

#include "simulation.hpp"

void print (world const& population)
{
    auto const clear = "\033[2J";
    int n = population.side();
    std::cout << clear;
    std::cout << '+' << std::string(n, '-') << "+\n";
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
    std::cout << '+' << std::string(n, '-') << "+\n";
}

int main()
{
    world population(50);
    double beta;
    double gamma;
    int d_;
    std::cout << "insert beta's value " << '\n';
    std::cin >> beta;
    std::cout << "insert gamma's value " << '\n';
    std::cin >> beta;
    std::cout << "choose how many days of the pandemic simulation you want to see " << '\n';
    std::cin >> d_;


    std::default_random_engine eng{std::random_device{}()};
    std::uniform_int_distribution<int> dist{0, population.side()};
    
    try {
        
    for (int i = 0; i != population.side() * population.side() / 10; ++i) {
        int r = dist(eng);
        int c = dist(eng);
        for (; population.person(r, c) == people::i_; r = dist(eng), c = dist(eng));
        population.person(r, c) = people::i_;
    }

    for (int i = 0; i != d_; ++i) {
        population = day_after(population, beta, gamma);
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