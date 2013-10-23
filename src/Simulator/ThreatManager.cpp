#include "../../include/Simulator/ThreatManager.hpp"
bool ClThreatManager::fire_static = false;
bool ClThreatManager::bomb_static = false;

ClThreatManager::ClThreatManager()
{
    bomb_texture.loadFromFile("pictures/bomb_tex.png");
    fire_texture.loadFromFile("pictures/fire_tex.png");
}

ClThreatManager::~ClThreatManager() {}

void ClThreatManager::createThreat(bool bomb, bool fire, const sf::Vector2f position)
{
    sf::Vector2f size_threat(40,40);
    if(bomb)
    {
        threat = new ClThreat(true, false, position, size_threat, bomb_texture);
        bomb = false;
        threatVector.push_back(threat);
    }
    if(fire)
    {
        threat = new ClThreat(false, true, position, size_threat, fire_texture);
        fire = false;
        threatVector.push_back(threat);
    }
}

void ClThreatManager::draw(sf::RenderWindow &window)
{
    for(unsigned int n=0; n<threatVector.size(); n++)
    {
        threatVector[n]->draw(window);
    }
}

//called from SimpleGUI (after button check)
void ClThreatManager::buttonPressed(bool bomb, bool fire)
{
    if(bomb)
    {
        bomb_static = true;
    }

    if(fire)
    {
        fire_static = true;
    }
}

//called in Simulation to update all threats (position) and create threats according to buttonPressed
void ClThreatManager::update(sf::RenderWindow &window, bool mouseReleased)
{
    if(bomb_static)
    {
        createThreat(true,false, sf::Vector2f (1190,550));
        bomb_static = false;
    }

    if(fire_static)
    {
        createThreat(false, true, sf::Vector2f (1140,550));
        fire_static = false;
    }

    for(unsigned int n=0; n<threatVector.size(); n++)
    {
        if(mouseReleased)
        {
            //new check for mouse action
            threatVector[n]->recognizeMouse(window);
        }

        //if there was a mouse action
        if(threatVector[n]->isMoved == true)
        {
            //set new position for each threat
            mouse = sf::Mouse::getPosition(window);
            threatVector[n]->setPosition((float)mouse.x,(float)mouse.y);
        }
    }
}
