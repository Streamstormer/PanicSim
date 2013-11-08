#ifndef BOMB_HPP_INCLUDED
#define BOMB_HPP_INCLUDED

#include "Threat.hpp"

class ClBomb : public ClThreat
{
public:
    ClBomb(const sf::Vector2f &position_threat, const sf::Vector2f &size_threat, const sf::Texture &texture_threat, ClArea *pArea, ClHeatMap *pHeatMap, ClStatistic *pStatistic,const sf::Texture &explosion_texture);
    void recognizeMouse(sf::RenderWindow &window);
    void activate();
    bool getFire();
    bool getBomb();
};

#endif // BOMB_HPP_INCLUDED
