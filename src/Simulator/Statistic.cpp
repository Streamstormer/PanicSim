#include "../../include/Simulator/Statistic.hpp"

ClStatistic::ClStatistic()
{
    numberBomb = 0;
    numberFire = 0;
}

ClStatistic::~ClStatistic()
{
    delete pAllCells;
}

void ClStatistic::planHeatMapStatistic(sf::Vector2i cellNumber)
{
    this->cellNumber = cellNumber;
    pAllCells = new int*[cellNumber.y];
    loopNumber = 0;
    for (int n=0; n < cellNumber.y; n++)
    {
        pAllCells[n] = new int[cellNumber.x];
    }

    for(int m=0; m<cellNumber.y; m++)
    {
        for(int n=0; n<cellNumber.x; n++)
        {
            pAllCells[m][n] = 0;
        }
    }
}

void ClStatistic::rememberCells(int cellX, int cellY, const int numberOfPeople)
{
    pAllCells[cellY][cellX] += numberOfPeople;
}

void ClStatistic::rememberLoop()
{
    loopNumber++;
}

void ClStatistic::rememberThreats(bool bomb, bool fire)
{
    if(bomb == true)
    {
        numberBomb++;
    }

    if(fire == true)
    {
        numberFire++;
    }
}

void ClStatistic::doCalculations()
{
    for(int m = 0; m<cellNumber.y; m++)
    {
        for(int n=0; n<cellNumber.x; n++)
        {
            pAllCells[m][n] = (int)(pAllCells[m][n]/loopNumber);
            std::cerr<<"Durchschitt Zelle["<<m<<"]["<<n<<"]: "<<pAllCells[m][n]<<std::endl;
        }
    }
    std::cerr<<"activated bombs: "<<numberBomb<<std::endl;
    std::cerr<<"activated fires: "<<numberFire<<std::endl;
}
