#ifndef PEOPLE_HPP_INCLUDED
#define PEOPLE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

const int PEOPLE_POSITION_MEMORY = 4;

struct StrPeople
{
    sf::Vector2f position[PEOPLE_POSITION_MEMORY];
    sf::Vector2f force;
    bool alive;             // used to make sure pointer on person is deleted everywhere
};

#endif // PEOPLE_HPP_INCLUDED
