#ifndef THREAT_HPP_INCLUDED
#define THREAT_HPP_INCLUDED
#include <vector>
#include <SFML/Graphics.hpp>
#include "Area.hpp"

class ClThreat
{
public:
    ClThreat(bool bomb, bool fire, const sf::Vector2f &position_threat, const sf::Vector2f &size_threat, const sf::Texture &texture_threat, ClArea *pArea);
    ~ClThreat();
    void draw(sf::RenderWindow &window);
    static void toggleDraw();
    void recognizeMouse(sf::RenderWindow &window);
    bool isMoved;
    void setPosition(float x_Position, float y_Position);
    sf::Vector2i mousePosition;
private:
    bool bomb;
    bool fire;
    //sf::Vector2f position_threat;
    //sf::Vector2f size_threat;
    sf::Sprite sprite_threat;
    sf::IntRect threat;
    ClArea *pArea;
};

#endif // THREAT_HPP_INCLUDED
