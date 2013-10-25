#include "../../include/Simulator/Threat.hpp"
#include <iostream>

//Creation of threats using a specific position, a size and one of the two possible textures (fire or bomb)
ClThreat::ClThreat(bool bomb, bool fire, const sf::Vector2f &position_threat, const sf::Vector2f &size_threat, const sf::Texture &texture_threat, ClArea *pArea)
{
    this->bomb = bomb;
    this->fire = fire;
//    this->position_threat = position_threat;
//    this->size_threat = size_threat;

//Threat gets this position and texture
    sprite_threat.setPosition(position_threat);
    sprite_threat.setTexture(texture_threat);

//Threat is an IntRect which is used to calculate if the mouse is contained in the threat (recognizeMouse())
    threat.left = position_threat.x-(0.5*(sprite_threat.getGlobalBounds().width));
    threat.top = position_threat.y-(0.5*(sprite_threat.getGlobalBounds().height));
    threat.width = sprite_threat.getGlobalBounds().width;
    threat.height = sprite_threat.getGlobalBounds().height;

//at the start: the threat is not moved (calculate in recognizeMouse())
    isMoved = false;

//Vector to set the origin in the middle of the threat
    sf::Vector2f sizeT(sprite_threat.getGlobalBounds().width, sprite_threat.getGlobalBounds().height);
    sprite_threat.setOrigin(sizeT.x/2,sizeT.y/2);

    this->pArea = pArea;
}

ClThreat::~ClThreat() {}

void ClThreat::draw(sf::RenderWindow &window)
{
    //draw threat with position
    window.draw(sprite_threat);
}

void ClThreat::recognizeMouse(sf::RenderWindow &window)
{
    mousePosition = sf::Mouse::getPosition(window);
    if(threat.contains(mousePosition))
    {
        if(isMoved==false)
        {
            isMoved = true;
        }
        else
        {
            sf::Vector2f mouseFloat((float)mousePosition.x, (float)mousePosition.y);
            //check if the threat is a fire and if yes - check for valid point in a static object
            if(fire)
            {
                isMoved = pArea->validPoint(mouseFloat);
            }
            else
            {
                isMoved = false;
            }
        }
    }
}

//set new threat position
void ClThreat::setPosition(float x_Position, float y_Position)
{
    sprite_threat.setPosition(x_Position, y_Position);
    threat.left = x_Position-(0.5*(sprite_threat.getGlobalBounds().width));
    threat.top = y_Position-(0.5*(sprite_threat.getGlobalBounds().height));
}
