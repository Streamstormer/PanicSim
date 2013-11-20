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
        const sf::Vector2f getClosestExitPoint(ClStaticObject *closestExit, const sf::Vector2f myPosition, int numOfExitPoints);
    protected:
    private:

};

#endif // CLEXITPOINTSELECTION_HPP
