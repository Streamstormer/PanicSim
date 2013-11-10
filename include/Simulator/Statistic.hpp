/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    handling all statistic calculations (in HeatMap, by creation of threats, time for evacuation, number of casualties)
---------------------------------------------------------------------------------------------------------------------------------------
*/

#ifndef STATISTIC_HPP_INCLUDED
#define STATISTIC_HPP_INCLUDED
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Diagramm.hpp"

class ClStatistic
{
public:
    ClStatistic(ClDiagramm *pDiagramm);
    ~ClStatistic();
    void planHeatMapStatistic(sf::Vector2i cellNumber, sf::Vector2f cellSize, const int sw_green, const int sw_yellow, const int sw_red);
    void rememberCells(int cellX, int cellY, const int numberOfPeople);
    void rememberLoopNumber();
    void rememberLoop();
    void rememberThreats(bool type_bomb, bool type_fire);
    void update(float frameTime);
    void drawStatistic(sf::RenderWindow &window);
    void drawDiagramm(sf::RenderWindow &window);
    void rememberKills(int number, bool bomb);
    static void setDoDrawStatistic(bool newBool);
    static void toggleDiagrammDraw();
    static void setInStatistic(bool active);
    static void rememberSpeed(int newSpeed);

    static int* getNumberBomb();
    static int* getNumberFire();
    static int* getNumberKillsBomb();
    static int* getNumberKillsFire();
    static int* getTime();
    static int* getSpeed();
    static int* getNumberCasualties();
    static void drawDiagramm();
    static void reset();
private:
    ClDiagramm *pDiagramm;
    sf::Clock startClock;
    sf::Clock pauseClock;
    sf::Clock fastClock;
    sf::Clock fasterClock;
    sf::Vector2i cellNumber;
    sf::Vector2f cellSize;
    sf::Color getColor(int people);
    int sw_green;
    int sw_yellow;
    int sw_red;
    int loopNumber;
    bool panic;
    int **pAllCells;
    int **pDrawCells;
    float frameTime;
    int time;

    static bool doDrawStatistic;
    static bool doDrawDiagramm;
    static bool inStatistic;
    static int numberFire;
    static int numberBomb;
    static int numberKillsBomb;
    static int numberKillsFire;
    static int numberCasualties;
    static int timeInSeconds;
    static int speed;
};

#endif // STATISTIC_HPP_INCLUDED
