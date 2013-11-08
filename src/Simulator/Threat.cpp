/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creation of threats, handling mouse action on threats and set new position according to mouse position
---------------------------------------------------------------------------------------------------------------------------------------
*/

#include "../../include/Simulator/Threat.hpp"

void ClThreat::subrecttoNumber(int number)
{
    subrect.top = (int)(number/ANIMATIONSQUARE)*subrect.height;
    subrect.left = (int)(number%ANIMATIONSQUARE)*subrect.width;
    explosion_sprite.setTextureRect(subrect);
    explosion_sprite.setPosition(sprite_threat.getPosition());
    explosion_sprite.setOrigin(subrect.width/2,subrect.height/2);
}

void ClThreat::draw(sf::RenderWindow &window)
{
    window.draw(sprite_threat);
    if (isActive)
    {
        // 1. calculate picture number from time
        // 2. chose correct picture
        if (bildID >63)
        {
            alive = false;
        }
        int time =animationTime.getElapsedTime().asMilliseconds();
        bildID = (int)time/PICTUREDURATION;
        subrecttoNumber(bildID);
        window.draw(explosion_sprite);
    }
}

//set new threat position
void ClThreat::setPosition(float x_Position, float y_Position)
{
    //1. set new position of threat (sprite which is drawn) according to the given float values
    //2. move IntRect "threat" (not drawn) accordingly for calculation if mouse is contained in threat (recognizeMouse())

    //1.
    sprite_threat.setPosition(x_Position, y_Position);
    //2.
    threat.left = x_Position-(0.5*(sprite_threat.getGlobalBounds().width));
    threat.top = y_Position-(0.5*(sprite_threat.getGlobalBounds().height));
}

//getter for isMoved
bool ClThreat::getIsMoved()
{
    return isMoved;
}

//getter for isActive
bool ClThreat::getIsActive()
{
    return isActive;
}
