#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "pandemic.prova.hpp"

//the way choosen the test the correct operation
//of the program is to check if he throws all the possible exception
//when the input parameters are not valid
TEST_CASE("testing pandemic")
{
    {
        population_state start{15, 13, 2, 0};
        pandemic p_0{start, 0.5, 0.5};
        CHECK_THROWS(p_0.values_checking());
    }

    {
        population_state start{15, 13, 2, 0};
        pandemic p_0{start, 0.1, 0.9};
        CHECK_THROWS(p_0.values_checking());
    }

    {
        population_state start{15, 13, 2, 0};
        pandemic p_0{start, -0.1, 0.5};
        CHECK_THROWS(p_0.values_checking());
    }

    {
        population_state start{15, 13, 2, 0};
        pandemic p_0{start, 0.5, -0.1};
        CHECK_THROWS(p_0.values_checking());
    }

    {
        population_state start{0, 13, 2, 0};
        pandemic p_0{start, 0.6, 0.5};
        CHECK_THROWS(p_0.values_checking());
    }

    {
        population_state start{15, 15, 0, 0};
        pandemic p_0{start, 0.6, 0.5};
        CHECK_THROWS(p_0.values_checking());
    }

    {
        population_state start{12, 39, 890, 9};
        pandemic p_0{start, 0.6, 0.5};
        CHECK_THROWS(p_0.values_checking());
    }

    {
        population_state start{15, 13, 2, 0};
        pandemic p_0{start, 0.6, 0.5};
        CHECK_THROWS(p_0.population_check(0));
        
    }

}
    
    