#ifndef PANDEMIC_HPP
#define PANDEMIC_HPP

#include <vector>
#include <cmath>
#include <iostream>

struct population_state
{
    //number of people analized
    //value inserted in input
    //must be an int positive number, greater than 0
    //n = susceptibles_ + infected_ + removed_
    int n_;

    //peoples that can be infected
    //in a pandemic simulated from the beginning the starting value
    //is near to n_
    int susceptibles_;

    //peoples that are infected
    //in a pandemic simulated from the beginnin the starting value
    //is near to 0
    int infected_;

    //dead or healed people
    //can't get infected and can't infect anymore
    int removed_;
    
};

//the following class will calculate the evolution of the pandemic
class pandemic
{
    private:
    population_state initial_state;
    //has to be a number included between 
    double beta_;
    double gamma_;
    public:

    //declaration of constructor, definition in pandemic.cpp
    pandemic(population_state const& population_0, double b_, double g_);

    //declaration of method value_checking
    //definition and more detailed comment in pandemic.cpp
    void values_checking();

    //declaration of method population_check
    //definition and more detailed comment in pandemic.cpp
    std::vector<population_state> population_check(int d);
};

#endif