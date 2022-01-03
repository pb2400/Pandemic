#ifndef PANDEMIC_CPP
#define PANDEMIC_CPP

#include <vector>
#include <cmath>
#include <iostream>

struct population_state
{
    // peoples that can be infected
    int susceptibles_;
    // peoples that are infected
    int infected_;
    //number of people analized
    int n_;
    // dead or healed people, that can't get infected and can't infect anymore
    int removed_;
    
};

// the following class will calculate the evolution of the pandemic

class pandemic
{
    population_state initial_state;
    double beta_;
    double gamma_;
    public:
    //you will be able calculate the evolution of the pandemic starting with
    //whatever value of the population you prefer 

    pandemic(population_state const& population_0, int duration_, double b_, double g_) 
    : initial_state{population_0}, beta_{b_}, gamma_{g_}
    {
         //some if to check if the starting value can be accepted
     if (beta_ <= 0 || beta_ > 1) {
        throw std::runtime_error{"beta value is not acceptable"};
    }

    if (gamma_ <= 0 || gamma_ > 1) {
        throw std::runtime_error{"gamma value is not acceptable"};
    }

    if (initial_state.n_ == 0) {
        throw std::runtime_error{"there must be at least one person in the population"};
    }
    }
    
    //this vector collets the datas of the population 
    //day after day during the pandemic
    std::vector<population_state> population_check(int d)
    {
        if (d == 0) {
            throw std::runtime_error{"the pandemic has been set on day 0"};
        }
        // using a for loop that every time repeated adds a vector
        // that represents the state of the population that day

        std::vector<population_state> progression{initial_state};
        population_state p_s = progression.back();
        for (int i = 1; i != d; ++i ) {
            double bsni = beta_ * p_s.susceptibles_ / p_s.n_ * p_s.infected_;
            double gs = gamma_ * p_s.infected_;
            p_s.susceptibles_ -= bsni;
            p_s.infected_ += bsni - gs;

            // calculating the number of removed daily by subtracting the 
            // number of susceptibles and infected from the total number of people

            p_s.removed_ = p_s.n_ - p_s.susceptibles_ - p_s.infected_;
            progression.push_back(p_s);
            }
            return progression;
    }
    };


#endif