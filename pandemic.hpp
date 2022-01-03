#ifndef PANDEMIC_CPP
#define PANDEMIC_CPP

#include <vector>
#include <cmath>

struct population_state
{
    // peoples that can be infected
    int susceptibles;
    // peoples that are infected
    int infected;
    // dead or healed people, that can't get infected and can't infect anymore
    int removed;
}

class pandemic