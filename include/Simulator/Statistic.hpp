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
    void rememberRedCell(int x, int y);
    void rememberLoopNumber();
    void rememberLoop();
    void rememberThreats(bool type_bomb, bool type_fire);
    void update();
    void drawStatistic(sf::RenderWindow &window);
    void drawDiagramm(sf::RenderWindow &window);
    void rememberKills(int number, bool bomb);
    static void setDoDrawStatistic(bool newBool);
    static void toggleDiagrammDraw();
    static void startTimer();
    static void rememberStatisticTime();
    static void rememberPause();
    static void rememberContinue();
    static void rememberFast();
    static void rememberFaster();

    static int* getNumberBomb();
    static int* getNumberFire();
    static int* getNumberKillsBomb();
    static int* getNumberKillsFire();
    static int* getTime();
    static void drawDiagramm();
private:
    ClDiagramm *pDiagramm;
    sf::Clock startClock;
    sf::Clock pauseClock;
    sf::Clock fastClock;
    sf::Clock fasterClock;
    sf::Vector2i cellNumber;
    sf::Vector2f cellSize;
    int sw_green;
    int sw_yellow;
    int sw_red;
    sf::Color getColor(int people);
    int loopNumber;
    float startTime;
    float pauseTime;
    float fastTime;
    float fasterTime;
    bool checkPause;
    bool checkFast;
    bool checkFaster;
    bool waitTimeOver;
    int **pAllCells;
    int **pDrawCells;
    int **pRedCells;

    static bool setStop;
    static bool setStart;
    static bool setPause;
    static bool setContinue;
    static bool setFast;
    static bool setFaster;
    static bool doDrawStatistic;
    static bool doDrawDiagramm;
    static int numberFire;
    static int numberBomb;
    static int numberKillsBomb;
    static int numberKillsFire;
    static int time;
};

#endif // STATISTIC_HPP_INCLUDED
