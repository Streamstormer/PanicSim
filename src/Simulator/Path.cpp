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
        this->position = 0;
    }

ClPath::~ClPath()
{
    //dtor
}

sf::Vector2f ClPath::getNextVector()
{
    position++;
    return vectorPath[position-1];
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

bool ClPath::isLastVector()
{
    if( vectorPath.back() == vectorPath[vectorPath.size()-1] )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ClPath::drawPath(sf::RenderWindow & window)
{
    for(int paint = 0; paint < (int)vectorPath.size(); paint++)
    {
        sf::Vector2f position;
        position = vectorPath[paint];
        sf::CircleShape Node;
        Node.setPosition(position);
        Node.setFillColor(sf::Color::Green);
        Node.setRadius(4.0f);
        window.draw(Node);
    }
}
