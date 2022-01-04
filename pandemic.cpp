#include "pandemic.prova.hpp"

    //definition of pandemic constructor 
    pandemic::pandemic(population_state const& population_0, double b_, double g_) 
    : initial_state{population_0}, beta_{b_}, gamma_{g_}
    {
    }

    //definition of method values_checking
    //method's task is to check all the input values
    void pandemic::values_checking() 
    {

    //checks the value of beta_
     if (beta_ <= 0 || beta_ > 1) {
        throw std::runtime_error{"beta value is not acceptable"};
    }

    //checks the value of gamma_
    if (gamma_ <= 0 || gamma_ > 1) {
        throw std::runtime_error{"gamma value is not acceptable"};
    }

    //checks the value of initial_state
    if (initial_state.n_ <= 0) {
        throw std::runtime_error{"there must be at least one person in the population"};
    }

    //checks the ratio between beta and gamma
    //has to be greater than one to let the pandemic start
    if (beta_ / gamma_ <= 1) {
        throw std::runtime_error{"with these starting values of beta and gamma the pandemic won't start"};
    }

    //checks if there is at least one person infected
    if (initial_state.infected_ <= 0) {
        throw std::runtime_error{"there must be at least one person infected"};
    }

    //creating some references in order to make the next if
    //easier to read   
    int& n = initial_state.n_;
    int& s = initial_state.susceptibles_;
    int& i = initial_state.infected_;
    int& r = initial_state.removed_;

    //checks if the starting relation between the population members
    //is valid (n = s + i + r)
    if (n != s + i + r) {
        throw std::runtime_error{"s + i + r != n"};
    }

    }

    //definition of method population_check
    //this method's task is create a vector
    //that represents the number of 
    //susceptibles, infected and removed daily 
    std::vector<population_state> pandemic::population_check(int d)
    {
        //checking if the number of days is acceptable
        if (d <= 0) {
            throw std::runtime_error{"either the pandemic has been set on day 0 or the number of day is not valid"};
            }

        // using a for loop that every time repeated adds a member to the vector
        // that represents the state of the population that day
        std::vector<population_state> progression{initial_state};
        population_state p_s = progression.back();
        for (int i = 1; i != d; ++i ) {
            double bsni = beta_ * p_s.susceptibles_ / p_s.n_ * p_s.infected_;
            double gs = gamma_ * p_s.infected_;
            p_s.susceptibles_ -= bsni;
            p_s.infected_ += bsni - gs;

            // calculating the number of removed people daily by subtracting the 
            // number of susceptibles and infected from the total number of people
            p_s.removed_ = p_s.n_ - p_s.susceptibles_ - p_s.infected_;
            progression.push_back(p_s);
            }
            return progression;
    }

