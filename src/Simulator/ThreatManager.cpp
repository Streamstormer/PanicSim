#include "../../include/Simulator/ThreatManager.hpp"
bool ClThreatManager::fire_static = false;
bool ClThreatManager::bomb_static = false;

ClThreatManager::ClThreatManager()
{
    bomb_texture.loadFromFile("pictures/bomb_texture.png");
    fire_texture.loadFromFile("pictures/fire_texture.png");
}

ClThreatManager::~ClThreatManager() {}

void ClThreatManager::createThreat(bool bomb, bool fire, const sf::Vector2f position)
{
    ClThreat *threat;
    sf::Vector2f size_threat(0,0);

    if(bomb)
    {
        threat = new ClThreat(true, false, position, size_threat, bomb_texture);
        bomb = false;
    }
    threatVector.push_back(threat);
}

void ClThreatManager::draw(sf::RenderWindow &window)
{
    for(unsigned int n=0; n<threatVector.size(); n++)
    {
        threatVector[n]->draw(window);
    }
}

void ClThreatManager::buttonPressed(bool bomb, bool fire)
{
    if(bomb)
    {
        bomb_static = true;
        fire_static = false;
    }
}

void ClThreatManager::update(sf::RenderWindow &window)
{
    if(bomb_static)
    {
        createThreat(true,false, sf::Vector2f (1190,550));
        bomb_static = false;
    }

    for(unsigned int n=0; n<threatVector.size(); n++)
    {
        threatVector[n]->recognizeMouse(window);
        if(threatVector[n]->isMoved == true)
        {
            std::cerr<<"Move"<<n<<std::endl;
            sf::Vector2i Mouse = sf::Mouse::getPosition(window);
            threatVector[n]->setPosition((float)Mouse.x,(float)Mouse.y);
            threatVector[n]->recognizeMouse(window);
        }
    }
}
