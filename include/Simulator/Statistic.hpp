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
    int loopNumber;
    static void toggleAverageDraw();
    static bool doDrawAverage;
    void rememberKills(int number, bool bomb);
    int getNumberBomb();
    int getNumberFire();
    int getNumberKillsBomb();
    int getNumberKillsFire();
private:
    sf::Vector2i cellNumber;
    sf::Vector2f cellSize;
    int sw_green;
    int sw_yellow;
    int sw_red;
    sf::Color getColor(int people);

    int **pAllCells;
    int **pDrawCells;
    int numberFire;
    int numberBomb;
    int numberKillsBomb;
    int numberKillsFire;
};

#endif // STATISTIC_HPP_INCLUDED
