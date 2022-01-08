#ifndef SIMULAZIONE_HPP
#define SIMULAZIONE_HPP

#include <vector>
#include <iostream>
//using s_, i_ r_ to represent 
//susceptibles, infected and removed people

enum class people {s_, i_, r_};

class world 
{
    using grid = std::vector<people>;
    int m_side;
    grid m_grid;

    //constructor
    public:
    world(int n) 
    : m_side(n), m_grid(m_side * m_side, people::s_)
    {
    }

    int side() const
    {
        return m_side;
    }

    std::vector<people> c_t()
    {
        return m_grid;
    }
    //commenta la conversione di indici
    people const& person(int r, int c) const 
    {
        auto const i = (r + m_side) % m_side;
        auto const j = (c + m_side) % m_side;
        if (i < 0 || i > m_side || j < 0 || j > m_side) {
            throw std::runtime_error{"unacceptable coordinates"};
        }
        auto const index = i * m_side + j;
        if (index <= 0 || index > static_cast<int>(m_grid.size()));
        return m_grid[index];
    }

    people& person(int r, int c) 
    {
        auto const i = (r + m_side) % m_side;
        auto const j = (c + m_side) % m_side;
        if (i < 0 || i > m_side || j < 0 || j > m_side) {
            throw std::runtime_error{"unacceptable coordinates"};
        }
        auto const index = i * m_side + j;
        if (index <= 0 || index > static_cast<int>(m_grid.size()));
        return m_grid[index];
    }
    friend bool operator ==(world const& l, world const& r)
    {
        return l.m_grid == r.m_grid;
    }
};

//counter
inline int neighbours_infected(world const& population_, int r, int c)
{
    int n_i = -static_cast<int>(population_.person(r, c));
    if (population_.person(r, c) == people::r_) {n_i += 2;}
    for (int i : {-1, 0, 1}) {
        for (int j : {-1, 0, 1}) {
            if (population_.person(r + i, c + j) == people::i_) {
                n_i += 1;
            }
        }
    }
    return n_i;
}

inline world day_after(world const& present, double beta_, double gamma_)
{   
    if (beta_ <= 0 || beta_ >= 1) {
        throw std::runtime_error{"beta's value is not acceptable"};
    }
    if (gamma_ <= 0 || gamma_ >= 1) {
        throw std::runtime_error{"gamma's value is not acceptable"};
    }
    if (beta_ / gamma_ <= 1) {
            throw std::runtime_error{"beta and gamma ratio is unacceptable"};
        }
    int const n = present.side();
    world evolved(n);
    for (int i = 0; i != n; ++i) { 
        for (int j = 0; j != n; ++j) { 
            int a = neighbours_infected(present, i, j);

        if (beta_ >= 0.5 && gamma_ <= 0.5) {
            a +=2;
        }
        if (beta_ > 0.5 && gamma_ > 0.5) {
            a += 1;
        }
        int const& inf_ = a;
        if (inf_ >= 4) {
            if (present.person(i, j) == people::s_) {
                evolved.person(i, j) = people::i_;
            } else {
                evolved.person(i, j) = people::r_;
            }
        } else {
            if (present.person(i, j) == people::s_) {
                evolved.person(i, j) = present.person(i, j);
            } else {
                evolved.person(i, j) = people::r_;
            }
        }
        }       
    }
    return evolved;
}


#endif