#ifndef FASTSQUAREROOT_HPP
#define FASTSQUAREROOT_HPP

#include <math.h>
#include <iostream>

const int NOPCS = 10000; // number of previous calculated squareroots

class ClFastSquareroot
{
    public:
    ClFastSquareroot()
    {
        if(firstRun)
        {
        for(int n = 0; n < NOPCS; n++)
        {
            squareroots[n] = sqrt(n);
        }
        firstRun = false;
        }

    }
    ~ClFastSquareroot() {}
    float getSqrt(int here)
    {
        if(here < NOPCS)
        {
            return squareroots[here];
        }
        else
        {
            std::cerr << "h:" << here << std::endl;
            return sqrt(here);
        }
    }
    private:
    static float squareroots[NOPCS];
    static bool firstRun;
};

#endif // FASTSQUAREROOT_HPP
