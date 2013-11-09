/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Patrick Senneka
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    Path stores the Nodes of the shortest Path in the right order.
---------------------------------------------------------------------------------------------------------------------------------------
*/
#include "../../include/Simulator/Path.hpp"

ClPath::ClPath(const sf::Vector2f & startVector)
    {
        this->vectorPath.push_back(startVector);
    }

ClPath::~ClPath()
{
    //dtor
}

sf::Vector2f ClPath::getNodePosition(int index)
{
    return vectorPath[index];
}

int ClPath::getFirstNodeId()
{
    return 1;
}

bool ClPath::isLast(int index)
{
    if( vectorPath[index] == vectorPath[vectorPath.size()-1] )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ClPath::addVector(const sf::Vector2f & add)
{
    this->vectorPath.push_back(add);
}

int ClPath::getSize()
{
    return vectorPath.size();
}

void ClPath::clearVectorPath()
{
    vectorPath.clear();
}

void ClPath::drawPath(sf::RenderWindow & window)
{
    sf::CircleShape Node;

    Node.setFillColor(sf::Color::Green);
    Node.setRadius(4.0f);

    for(int paint = 0; paint < (int)vectorPath.size(); paint++)
    {
        Node.setPosition(vectorPath[paint]);
        window.draw(Node);
    }
}
