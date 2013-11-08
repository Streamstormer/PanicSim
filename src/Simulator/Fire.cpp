/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creation of fire, handling mouse action on fire and set new position according to mouse position
---------------------------------------------------------------------------------------------------------------------------------------
*/

#include "../../include/Simulator/Fire.hpp"

ClFire::ClFire(const sf::Vector2f &position_threat, const sf::Vector2f &size_threat, const sf::Texture &texture_threat, ClArea *pArea, ClHeatMap *pHeatMap, ClStatistic *pStatistic)
{
    this->position_threat = position_threat;
    this->size_threat = size_threat;
    this->pArea = pArea;
    this->pHeatMap = pHeatMap;
    this->pStatistic = pStatistic;

//threat is movable, not active but alive at the beginning
    isActive = false;
    alive = true;
    isMoved = true;

//Threat gets this position and texture
    sprite_threat.setPosition(position_threat);
    sprite_threat.setTexture(texture_threat);

//"threat" is an IntRect which is used to calculate if the mouse is contained in the threat (recognizeMouse())
    threat.left = position_threat.x-(0.5*(sprite_threat.getGlobalBounds().width));
    threat.top = position_threat.y-(0.5*(sprite_threat.getGlobalBounds().height));
    threat.width = sprite_threat.getGlobalBounds().width;
    threat.height = sprite_threat.getGlobalBounds().height;

//set the origin in the middle of the threat
    sf::Vector2f sizeT(sprite_threat.getGlobalBounds().width, sprite_threat.getGlobalBounds().height);
    sprite_threat.setOrigin(sizeT.x/2,sizeT.y/2);

    type = THFIRE;
}

//draw fire sprite
void ClFire::draw(sf::RenderWindow &window)
{
    window.draw(sprite_threat);
}


void ClFire::recognizeMouse(sf::RenderWindow &window)
{
    //1. take position of mouse
    //2. if mouse is contained in IntRect "threat"
    //3. check if threat is moved actually
    //3.1       if threat is not moving - click causes start of move
    //3.2       if threat is moving -> 4.
    //4  check if mouse (as float vector) is set on a valid point (on a buidling in area)
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
            //4
            sf::Vector2f mouseFloat((float)mousePosition.x, (float)mousePosition.y);
            //5.
            isMoved = pArea->validPoint(mouseFloat);
        }
    }
}

//activate fire
void ClFire::activate()
{
    //1. if it´s not active - activate fire
    //2. set fire as "not alive"
    //3. fire up static object around
    ///4. will come: remember casualties by fire

    //1.
    if(isActive == false)
    {
        isActive = true;
        //2.
        alive = false;
        //3.
        pArea->setOnFire(pArea->getIdByVector(sf::Vector2f(threat.left + (threat.width / 2), threat.top + (threat.height/2))));
    }
}
