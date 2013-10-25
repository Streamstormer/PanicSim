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
    sf::Vector2i mouse;
private:
    std::vector<ClThreat *> threatVector;
    sf::Texture bomb_texture;
    sf::Texture fire_texture;
    static bool fire_static;
    static bool bomb_static;
    ClThreat *threat;
    sf::Image image;
    ClArea *pArea;
};

#endif // THREATMANAGER_HPP_INCLUDED
