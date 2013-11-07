/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creation of threats, handling mouse action on threats and set new position according to mouse position
---------------------------------------------------------------------------------------------------------------------------------------
*/

#include "../../include/Simulator/Threat.hpp"
#include <iostream>

//Creation of threats on an area using a specific position, a size and one of the two possible textures (fire or bomb)
ClThreat::ClThreat(bool bomb, bool fire, const sf::Vector2f &position_threat, const sf::Vector2f &size_threat, const sf::Texture &texture_threat, ClArea *pArea, ClHeatMap *pHeatMap, ClStatistic *pStatistic,const sf::Texture &explosion_texture)
{
//boolean values for differentiation
    this->bomb = bomb;
    this->fire = fire;

//attributes of each threat
    this->position_threat = position_threat;
    this->size_threat = size_threat;
    this->pArea = pArea;
    this->pHeatMap = pHeatMap;
    this->pStatistic = pStatistic;

//threat is not active at the beginning
    isActive = false;

//Threat gets this position and texture
    sprite_threat.setPosition(position_threat);
    sprite_threat.setTexture(texture_threat);

//"threat" is an IntRect which is used to calculate if the mouse is contained in the threat (recognizeMouse())
    threat.left = position_threat.x-(0.5*(sprite_threat.getGlobalBounds().width));
    threat.top = position_threat.y-(0.5*(sprite_threat.getGlobalBounds().height));
    threat.width = sprite_threat.getGlobalBounds().width;
    threat.height = sprite_threat.getGlobalBounds().height;

//at the start: the threat is moved (new calculation in recognizeMouse() after button is released)
    isMoved = true;

//set the origin in the middle of the threat
    sf::Vector2f sizeT(sprite_threat.getGlobalBounds().width, sprite_threat.getGlobalBounds().height);
    sprite_threat.setOrigin(sizeT.x/2,sizeT.y/2);

//set explosion texture
    explosion_sprite.setTexture(explosion_texture);
    subrect.top=0;
    subrect.left=0;
    subrect.width=explosion_texture.getSize().x/8;
    subrect.height=explosion_texture.getSize().y/8;
    bildID=0;


}

ClThreat::~ClThreat() {}

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
            bildID=63;//isActive=false;
        }
        int time =animationTime.getElapsedTime().asMilliseconds();
        bildID = (int)time/PICTUREDURATION;
        subrecttoNumber(bildID);
        window.draw(explosion_sprite);

    }


}

//is only called if there is a mouse action (left mouse button released) in main function
void ClThreat::recognizeMouse(sf::RenderWindow &window)
{
    //1. take position of mouse
    //2. if mouse is contained in IntRect "threat"
    //3. check if threat is moved actually
    //3.1       if threat is not moving - click causes start of move
    //3.2       if threat is moving -> 4.
    //4. differentaition if threat is a bomb -> 4.1 if it is a fire -> 4.2
    //4.1 click causes stop of move
    //4.2 check if mouse (as float vector) is set on a valid point (on a buidling in area)
    //5. if valid point stop moving otherwise continue moving with mouse

    //1.
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    //2.
    if(threat.contains(mousePosition))
    {
        //3.
        if(isMoved==false)
        {
            //3.1
            isMoved = true;
        }
        //3.2
        else
        {
            //4.
            if(fire)
            {
                //4.2
                sf::Vector2f mouseFloat((float)mousePosition.x, (float)mousePosition.y);
                //5.
                isMoved = pArea->validPoint(mouseFloat);
            }
            else
            {
                //4.1
                isMoved = false;
            }
        }
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

bool ClThreat::getIsActive()
{
    return isActive;
}


void ClThreat::activate()
{
    isActive = true;
    int casualties = pHeatMap->explosion(sf::Vector2f(threat.left + (threat.width / 2), threat.top + (threat.height/2)), 100);
    pStatistic->rememberKills(casualties, bomb);
    animationTime.restart();

}

bool ClThreat::getBomb()
{
    return bomb;
}

bool ClThreat::getFire()
{
    return fire;
}

