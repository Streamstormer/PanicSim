/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Lukas
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    Simple Struct storing the information about persons
---------------------------------------------------------------------------------------------------------------------------------------
*/

#ifndef PEOPLE_HPP_INCLUDED
#define PEOPLE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

// used for Filtering Position
const int PEOPLE_POSITION_MEMORY = 4;
const int COLLISION_POSITION_MEMORY = 4;

struct StrPeople
{
    sf::Vector2f position[PEOPLE_POSITION_MEMORY];
    sf::Vector2f positonMemory[COLLISION_POSITION_MEMORY]; //use to determine weather people are pushed into buildings and killed
    sf::Vector2f force;
    bool alive;             // used to make sure pointer on person is deleted everywhere
    bool panic;             // used to ensure that people can get infected by panic
    int currentNode;        // used to seek for the next node
};

#endif // PEOPLE_HPP_INCLUDED
