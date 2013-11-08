/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Patrick Senneka
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creates a diagramm which shows the number of casualties and threads over the time
---------------------------------------------------------------------------------------------------------------------------------------
*/
#ifndef DIAGRAMM_HPP_INCLUDED
#define DIAGRAMM_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


class ClDiagramm
{
public:
    ClDiagramm(const sf::Vector2f & position, float diagrammSizeX, float diagrammSizeY);
    ~ClDiagramm();
    void registerFire();
    void registerBomb();
    void registerCasualties();
    void draw(sf::RenderWindow & window);


private:
    int id;
    sf::Clock clock;
    float diagrammSizeX, diagrammSizeY;
    sf::Vector2f position;
    sf::Sprite spriteDiagramm;
    const int NUMBERBLOCKS = 8;
    const int OFFSET = 50;

    sf::Font font;

    typedef enum{
    BOMB,
    FIRE,
    CASUALTIES
    }EVENTTYPE;

    typedef struct{
    int id;
    EVENTTYPE TYPE;
    sf::Time time;
    }event;

    std::vector<event> eventsVector;

    void drawBackground(sf::RenderWindow & window);
    void drawXAxis(sf::RenderWindow & window);
    void drawYAxis(sf::RenderWindow & window);

};
#endif // DIAGRAMM_HPP_INCLUDED
