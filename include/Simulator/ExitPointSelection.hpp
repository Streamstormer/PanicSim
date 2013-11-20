/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Manuel Stampp
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    called for big EXIT staticobjects to partition it into more exit points
            and choose the nearest for a Crowd
---------------------------------------------------------------------------------------------------------------------------------------
*/

#ifndef CLEXITPOINTSELECTION_HPP
#define CLEXITPOINTSELECTION_HPP

#include "StaticObject.hpp"
#include "FastSquareroot.hpp"


const unsigned int EXIT_POINT_DISTANCE = 50;

class ClExitPointSelection
{
    public:
        ClExitPointSelection();
        virtual ~ClExitPointSelection();
        //Partitions the exit into more attraction points,
        //returns the posítion vector of the nearest of these to the parameter myPosition
        const sf::Vector2f getClosestExitPoint(ClStaticObject *closestExit, const sf::Vector2f myPosition, int numOfExitPoints);
    protected:
    private:

};

#endif // CLEXITPOINTSELECTION_HPP
