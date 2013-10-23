#include "../../include/Simulator/Threat.hpp"
#include <iostream>

bool ClThreat::drawFire = false;
bool ClThreat::drawBomb = false;

ClThreat::ClThreat(bool bomb, bool fire, const sf::Vector2f &position_threat, const sf::Vector2f &size_threat, const sf::Texture &texture_threat)
{
    this->bomb = bomb;
    this->fire = fire;
//    this->position_threat = position_threat;
//    this->size_threat = size_threat;

    sprite_threat.setPosition(position_threat);
    sprite_threat.setTexture(texture_threat);

    threat.left = position_threat.x;
    threat.top = position_threat.y;
    threat.width = sprite_threat.getGlobalBounds().width;
    threat.height = sprite_threat.getGlobalBounds().height;
    isMoved = false;
}

ClThreat::~ClThreat() {}

void ClThreat::draw(sf::RenderWindow &window)
{
    recognizeMouse(window);
    window.draw(sprite_threat);
}

void ClThreat::recognizeMouse(sf::RenderWindow &window)
{
    sf::Event event2;
    window.pollEvent(event2);
    if(threat.contains(sf::Mouse::getPosition(window)) && event2.type == sf::Event::MouseButtonReleased && event2.mouseButton.button==sf::Mouse::Left)
    {
        if(isMoved==false)
        {
            std::cerr<<"Move threat!"<<std::endl;
            isMoved = true;
        }else isMoved = false;

    }
}

void ClThreat::setPosition(float x_Position, float y_Position)
{
    sprite_threat.setPosition(x_Position, y_Position);
    threat.left = x_Position;
    threat.top = y_Position;
}
