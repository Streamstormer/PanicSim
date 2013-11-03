#ifndef PEOPLE_HPP_INCLUDED
#define PEOPLE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

struct StrPeople
{
    sf::Vector2f position;
    sf::Vector2f force;
    bool alive;             // used to make sure pointer on person is deleted everywhere
};

#endif // PEOPLE_HPP_INCLUDED
