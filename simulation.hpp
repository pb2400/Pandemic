#ifndef SIMULAZIONE_GRAPHYCH_HPP
#define SIMULAZIONE_GRAPHYCH_HPP

#include <vector>
#include <iostream>


enum class people{s_, i_, r_};

//all the methods of the class world and all the free function declared
//in this file are defined in simulation.cpp file
//look in simulation.cpp file also for the description of
//each method and free class funcionality

class world 
{
    private:
    using grid = std::vector<people>;
    int m_side;
    grid m_grid;

    public:
    //constructor
    world(int n);

    //method size
    int side() const;

    //method people
    people const& person(int r, int c) const;

    //overloading of method people
    people& person(int r, int c);
    
    //definition of operator ==
    //defines the operation of == between tho object
    //of world type
    friend bool operator ==(world const& l, world const& r)
    {
        return l.m_grid == r.m_grid;
    }
};



//definition of free function neighbours_infected
int neighbours_infected(world const& population_, int r, int c);

//definition of free function day_after
world day_after(world const& present, double beta_, double gamma_);
