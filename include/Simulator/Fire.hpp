#ifndef FIRE_HPP_INCLUDED
#define FIRE_HPP_INCLUDED

#include "Threat.hpp"

class ClFire : public ClThreat
{
public:
    ClFire(const sf::Vector2f &position_threat, const sf::Vector2f &size_threat, const sf::Texture &texture_threat, ClArea *pArea, ClHeatMap *pHeatMap, ClStatistic *pStatistic, const sf::Texture &explosion_texture);
    void recognizeMouse(sf::RenderWindow &window);
    void activate();
    bool getFire();
    bool getBomb();
};

#endif // FIRE_HPP_INCLUDED
