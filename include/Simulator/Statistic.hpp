#ifndef STATISTIC_HPP_INCLUDED
#define STATISTIC_HPP_INCLUDED
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

class ClStatistic
{
public:
    ClStatistic(sf::Vector2i cellNumber);
    ~ClStatistic();
    void rememberCells(int cellX, int cellY, const int numberOfPeople);
    void rememberLoopNumber();
    void doCalculation();
    void rememberLoop();
private:
    sf::Vector2i cellNumber;
    int loopNumber;
    int **pAllCells;
};

#endif // STATISTIC_HPP_INCLUDED
