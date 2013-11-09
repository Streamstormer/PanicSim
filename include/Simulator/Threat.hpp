/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    abstract class for creation of different threats, handling mouse action on threats and set new position according to mouse position
---------------------------------------------------------------------------------------------------------------------------------------
*/

#ifndef THREAT_HPP_INCLUDED
#define THREAT_HPP_INCLUDED
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Area.hpp"
#include "HeatMap.hpp"
#include "Diagramm.hpp"

enum ThreatType {THBOMB, THFIRE};

class ClThreat
{
public:
    //virtual kann überschrieben werden  -  virtual + const muss
    virtual ~ClThreat();
    virtual void recognizeMouse(sf::RenderWindow &window) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    bool getIsMoved();
    void setPosition(float x_Position, float y_Position);
    bool getIsActive();
    virtual void activate() = 0;
    enum ThreatType getType();
    bool getAlive(){return alive;}
protected:
    enum ThreatType type;
    void subrecttoNumber(int number);
    ClHeatMap *pHeatMap;
    ClDiagramm *pDiagramm;
    bool isMoved;
    bool isActive; // bomb explodes fire starts to burn
    bool alive;
    sf::Vector2f position_threat;
    sf::Vector2f size_threat;
    sf::Sprite sprite_threat;
    sf::Sprite explosion_sprite;
    sf::Clock animationTime;
    sf::IntRect threat;
    ClArea *pArea;
    ClStatistic *pStatistic;
    sf::Rect<int> subrect;
    int time;
    int bildID;
    const static int PICTUREDURATION =25;
    const static int ANIMATIONSQUARE =8;
};

#endif // THREAT_HPP_INCLUDED
