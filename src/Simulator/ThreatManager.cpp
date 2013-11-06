/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    handling threat creation, update and draw
---------------------------------------------------------------------------------------------------------------------------------------
*/

#include "../../include/Simulator/ThreatManager.hpp"
bool ClThreatManager::fire_static = false;
bool ClThreatManager::bomb_static = false;
bool ClThreatManager::explosion_static = false;

ClThreatManager::ClThreatManager(ClArea *pArea, ClStatistic *pStatistic, ClHeatMap *pHeatMap)
{
    this->pHeatMap = pHeatMap;
    //assigning the textures to variables
    bomb_texture.loadFromFile("pictures/bomb_tex.png");
    fire_texture.loadFromFile("pictures/fire_tex.png");

    //pointer to the original area
    this->pArea = pArea;
    //pointer to the statistic
    this->pStatistic = pStatistic;
}

ClThreatManager::~ClThreatManager()
{
    //delete all threats created
    for(unsigned int n=0; n<threatVector.size(); n++)
    {
        delete threatVector[n];
    }
}

void ClThreatManager::createThreat(bool bomb, bool fire, const sf::Vector2f position)
{
    //default threat size
    sf::Vector2f size_threat(40,40);

    //1. differentiation between fire or bomb
    //2. create new threat with position, size and according texture (give area for later calculations)
    //   push_back to threatVector

    //1.
    if(bomb)
    {
        //2.
        ClThreat *pThreat = new ClThreat(true, false, position, size_threat, bomb_texture, pArea, pHeatMap, pStatistic);
        threatVector.push_back(pThreat);
        bomb = false;
    }

    //1.
    if(fire)
    {
        //2.
        ClThreat *pThreat = new ClThreat(false, true, position, size_threat, fire_texture, pArea, pHeatMap, pStatistic);
        threatVector.push_back(pThreat);
        fire = false;
    }
}

void ClThreatManager::draw(sf::RenderWindow &window)
{
    //draw all threats containing in threatVector
    for(unsigned int n=0; n<threatVector.size(); n++)
    {
        threatVector[n]->draw(window);
    }
}

//called from SimpleGUI (after button check)
void ClThreatManager::buttonPressed(bool bomb, bool fire, bool explosion)
{
    //set static boolean according to pressed button
    if(bomb)
    {
        bomb_static = true;
    }
    if(fire)
    {
        fire_static = true;
    }
    if(explosion)
    {
        explosion_static = true;
    }
}

//called in Simulation to update all threats (position) and create threats according to buttonPressed
void ClThreatManager::update(sf::RenderWindow &window, bool mouseReleased)
{
    //1. calculate mouse position as float vector
    //2. check for new threats (are static boolean set or not)
    //3. if one is set -> create new threat -> set static boolean to false
    //4. check if theats should move (check all threats in threatVector)
    //5. if mouse button released (in event loop of main function)
    //6. check if pressed mouse is contained in the threat (set isMoved accordingly)
    //7. check for isMoved
    //8. if isMoved is true -> move sprite of this threat according to float mouse position

    /// explosion handling :
    //2.1. check for explosion
    //2.2. activate all inactive threats
    //2.3. tell the statistics about activated threats

    //1.
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    sf::Vector2f mouseFloat((float)mouse.x,(float)mouse.y);

    //2.
    if(bomb_static)
    {
        //3.
        createThreat(true,false, mouseFloat);
        bomb_static = false;
    }
    //2.
    if(fire_static)
    {
        //3.
        createThreat(false, true, mouseFloat);
        fire_static = false;
    }
    //4.
    for(unsigned int n=0; n<threatVector.size(); n++)
    {
        //5.
        if(mouseReleased)
        {
            //6.
            threatVector[n]->recognizeMouse(window);
        }
        //7.
        if(threatVector[n]->getIsMoved() == true)
        {
            //8.
            threatVector[n]->setPosition(mouseFloat.x, mouseFloat.y);
        }
    }

    // 2.1
    if (explosion_static)
    {
        for(unsigned int n = 0; n < threatVector.size(); n++)
        {
            // 2.2
            if(threatVector[n]->getIsActive()==false)
            {
                threatVector[n]->activate();
                // 2.3
                pStatistic->rememberThreats(threatVector[n]->getBomb(), threatVector[n]->getFire());
            }
        }
        explosion_static = false;
    }
}
