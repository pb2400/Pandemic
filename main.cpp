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
        std::cout << "| " << std::setw(9) << dates_.susceptilbes_ << " | " << std::setw(9)
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
    
}