#include <iomanip>
#include <iostream>

#include "pandemic.hpp"

//this function prints in a table the values
//of susceptibles, infected and removed
//day by day during the pandemic
void print(std::vector<population_state> const& pop_daily_)
{
    //building the table
    std::cout << "+-----------+-----------+-----------+\n"
                 "|     s     |     i     |     r     |\n"
                 "+-----------+-----------+-----------+\n";

    //building a for loop tha goes throuhg
    //the vector pop_daily_ and prints the values of 
    //s, r, i daily   
    //using std::setw from iomanip to set the 
    //field width to be used on output operations          
    for (auto& dates_ : pop_daily_) {
        std::cout << "| " << std::setw(9) << dates_.susceptibles_ << " | " << std::setw(9)
                  << dates_.infected_ << " | " << std::setw(9) << dates_.removed_ 
                  << " |\n";
    }
    std::cout << "+-----------+-----------+-----------+\n";            
}

//building the function main where the input will be made of
//beta and gamma parameters, starting values of susceptibles
//infected and removed, and the duration (in days) of the simulation

int main()
{
    //using int n_, s_, i_, r_ to represent the values of susceptibles, infected and removed
    //using g_, b_ and d_ to represent the values of gamma, beta and days
    int n_;
    int s_;
    int i_;
    int r_;
    int d_;
    double g_;
    double b_;
    std::cout << "insert the starting values of population: peoples, susceptibles, infected and removed " << '\n';
    std::cin >> n_ >> s_ >> i_ >> r_;
    std::cout << "insert the values of gamma and beta " << "\n";
    std::cin >> g_ >> b_; 
    std::cout << "estabilish the duration of the simulation in days " << '\n';
    std::cin >> d_;
    population_state day_0{n_, s_, i_, r_};

    //starting the try catch because pandemic could throw some runtime_errors
    try {
    pandemic simulation{day_0, b_, g_,};

    //calling the method values checking to check 
    //if the input values can be accepted
    simulation.values_checking();

    auto s_complete = simulation.population_check(d_);
    print(s_complete);
    } catch (std::exception const& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    } catch(...) {
        std::cerr << "something went wrong\n";
        return EXIT_FAILURE;
    }
}