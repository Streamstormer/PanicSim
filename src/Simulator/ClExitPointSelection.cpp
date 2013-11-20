#include "../../include/Simulator/ExitPointSelection.hpp"

ClExitPointSelection::ClExitPointSelection()
{
    //ctor
}

ClExitPointSelection::~ClExitPointSelection()
{
    //dtor
}

const sf::Vector2f ClExitPointSelection::getClosestExitPoint(ClStaticObject *closestExit, const sf::Vector2f myPosition, int numOfExitPoints)
{
    float distance = INFINITY;
    float testDistance = 0;
    sf::Vector2f closestExitPosition = closestExit->getPosition();

    sf::Vector2f mainPoint = closestExit->getMiddleOfLine();
    sf::Vector2f centerPoint = closestExit->getCenter();
    sf::Vector2f diffVect = sf::Vector2f(mainPoint.x - centerPoint.x, mainPoint.y - centerPoint.y);
    sf::Vector2f unitVect;
    sf::Vector2f attrPosWa;
    ClFastSquareroot fSR;
    float vectorDistance = fSR.getSqrt((diffVect.x) * (diffVect.x) + (diffVect.y) * (diffVect.y));
    if(vectorDistance != 0)
    {
        unitVect.x = diffVect.x / vectorDistance;
        unitVect.y = diffVect.y / vectorDistance;
    }
    else
    {
        std::cout << "Division by zero when calculating the Unit vector.";
    }
    std::cerr << "UnitVect: X: " << unitVect.x << ", Y: " << unitVect.y << "\n";

    if(abs(unitVect.x) < abs(unitVect.y))
    {
        mainPoint.x -= numOfExitPoints * EXIT_POINT_DISTANCE / 2 - EXIT_POINT_DISTANCE / 2;
    }
    else
    {
        mainPoint.y -= numOfExitPoints * EXIT_POINT_DISTANCE / 2 - EXIT_POINT_DISTANCE / 2;
    }

    attrPosWa = mainPoint;
    for(int i = 0; i < numOfExitPoints; i++)
    {
        testDistance = (myPosition.x - attrPosWa.x)
                       *(myPosition.x - attrPosWa.x)
                       +(myPosition.y - attrPosWa.y)
                       *(myPosition.y - attrPosWa.y);
        if (testDistance<distance)
        {
            mainPoint = attrPosWa;
            closestExitPosition = mainPoint;
            distance = testDistance;
        }
        //exitPoints.push_back(sf::Vector2f(attrPosWa.x - diffVect.x, attrPosWa.y - diffVect.y));
        if(abs(unitVect.x) < abs(unitVect.y))
        {
            attrPosWa.x += EXIT_POINT_DISTANCE;
        }
        else
        {
            attrPosWa.y += EXIT_POINT_DISTANCE;
        }
        std::cerr << "Iteration: " << i << "; X: " << closestExitPosition.x << ", Y:" << closestExitPosition.y << "\n";
    }

    closestExitPosition.x -= diffVect.x;
    closestExitPosition.y -= diffVect.y;
    std::cerr << "Returned value: " << closestExitPosition.x << ", " << closestExitPosition.y << "\n";
    return closestExitPosition;
}
