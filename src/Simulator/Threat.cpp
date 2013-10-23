#include "../../include/Simulator/Threat.hpp"
#include <iostream>

//Creation of threats using a specific position, a size and one of the two possible textures (fire or bomb)
ClThreat::ClThreat(bool bomb, bool fire, const sf::Vector2f &position_threat, const sf::Vector2f &size_threat, const sf::Texture &texture_threat)
{
    this->bomb = bomb;
    this->fire = fire;
//    this->position_threat = position_threat;
//    this->size_threat = size_threat;

//Threat gets this position and texture
    sprite_threat.setPosition(position_threat);
    sprite_threat.setTexture(texture_threat);

//Threat is an IntRect which is used to calculate if the mouse is contained in the threat (recognizeMouse())
    threat.left = position_threat.x;
    threat.top = position_threat.y;
    threat.width = sprite_threat.getGlobalBounds().width;
    threat.height = sprite_threat.getGlobalBounds().height;

//at the start: the threat is not moved (calculate in recognizeMouse())
    isMoved = false;
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
            isMoved = false;
        }
    }
}

//set new threat position
void ClThreat::setPosition(float x_Position, float y_Position)
{
    sprite_threat.setPosition(x_Position, y_Position);
    threat.left = x_Position;
    threat.top = y_Position;
}
