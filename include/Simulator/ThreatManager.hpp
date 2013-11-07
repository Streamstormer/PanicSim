/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    handling threat creation, update and draw
---------------------------------------------------------------------------------------------------------------------------------------
*/

#ifndef THREATMANAGER_HPP_INCLUDED
#define THREATMANAGER_HPP_INCLUDED
#include <vector>
#include "SimpleButton.hpp"
#include "Threat.hpp"
#include "Area.hpp"
#include "HeatMap.hpp"
#include "Statistic.hpp"

class ClThreatManager
{
public:
    ClThreatManager(ClArea *pArea, ClStatistic *pStatistic, ClHeatMap *pHeatMap);
    ~ClThreatManager();
    void update(sf::RenderWindow &window, bool mouseReleased);
    void draw(sf::RenderWindow &window);
    void createThreat(bool bomb, bool fire, const sf::Vector2f position);
    static void buttonPressed(bool bomb, bool fire, bool explosion);

private:
    ClArea *pArea;
    ClStatistic *pStatistic;
    ClHeatMap *pHeatMap; // for Threats so they can interact with people

    sf::Texture bomb_texture;
    sf::Texture fire_texture;
    sf::Texture explosion_texture;
    std::vector<ClThreat *> threatVector;
    static bool fire_static;
    static bool bomb_static;
    static bool explosion_static;
};
#endif // THREATMANAGER_HPP_INCLUDED
