#ifndef STATISTIC_HPP_INCLUDED
#define STATISTIC_HPP_INCLUDED
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class ClStatistic
{
public:
    ClStatistic();
    ~ClStatistic();
    void planHeatMapStatistic(sf::Vector2i cellNumber, sf::Vector2f cellSize, const int sw_green, const int sw_yellow, const int sw_red);
    void rememberCells(int cellX, int cellY, const int numberOfPeople);
    void rememberLoopNumber();
    void rememberLoop();
    void rememberThreats(bool bomb, bool fire);
    void update();
    void draw(sf::RenderWindow &window);
    void rememberKills(int number, bool bomb);
    static void setAverageDraw(bool newBool);
    static bool getAverageDraw();
    static void startTimer();
    static void rememberTime();
    static int* getNumberBomb();
    static int* getNumberFire();
    static int* getNumberKillsBomb();
    static int* getNumberKillsFire();
    static int* getTime();
private:
    sf::Clock startClock;
    sf::Vector2i cellNumber;
    sf::Vector2f cellSize;
    int sw_green;
    int sw_yellow;
    int sw_red;
    sf::Color getColor(int people);
    int loopNumber;
    int **pAllCells;
    int **pDrawCells;

    static bool setStop;
    static bool setStart;
    static bool doDrawAverage;
    static int numberFire;
    static int numberBomb;
    static int numberKillsBomb;
    static int numberKillsFire;
    static int time;
};

#endif // STATISTIC_HPP_INCLUDED
