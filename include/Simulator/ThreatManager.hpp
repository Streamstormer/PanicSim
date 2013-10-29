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

class ClThreatManager
{
public:
    ClThreatManager(ClArea *pArea);
    ~ClThreatManager();
    void update(sf::RenderWindow &window, bool mouseReleased);
    void draw(sf::RenderWindow &window);
    void createThreat(bool bomb, bool fire, const sf::Vector2f position);
    static void buttonPressed(bool bomb, bool fire);
private:
    ClArea *pArea;
    sf::Texture bomb_texture;
    sf::Texture fire_texture;
    std::vector<ClThreat *> threatVector;
    static bool fire_static;
    static bool bomb_static;
    ClThreat *pThreat;
};

#endif // THREATMANAGER_HPP_INCLUDED
