#include "../../include/Simulator/Fire.hpp"

ClFire::ClFire(const sf::Vector2f &position_threat, const sf::Vector2f &size_threat, const sf::Texture &texture_threat, ClArea *pArea, ClHeatMap *pHeatMap, ClStatistic *pStatistic, const sf::Texture &explosion_texture)
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

//set explosion texture
    explosion_sprite.setTexture(explosion_texture);
    subrect.top=0;
    subrect.left=0;
    subrect.width=explosion_texture.getSize().x/8;
    subrect.height=explosion_texture.getSize().y/8;
    bildID=0;
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

void ClFire::activate()
{
    if(isActive == false)
    {
        isActive = true;
        alive = false;
        pArea->setOnFire(pArea->getIdByVector(sf::Vector2f(threat.left + (threat.width / 2), threat.top + (threat.height/2))));
    }
}

bool ClFire::getFire()
{
    return true;
}

bool ClFire::getBomb()
{
    return false;
}
