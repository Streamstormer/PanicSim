#include "../../include/Simulator/Statistic.hpp"

ClStatistic::ClStatistic(sf::Vector2i cellNumber)
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

ClStatistic::~ClStatistic()
{
    delete pAllCells;
}

void ClStatistic::rememberCells(int cellX, int cellY, const int numberOfPeople)
{
    pAllCells[cellY][cellX] = numberOfPeople;
}

void ClStatistic::rememberLoopNumber()
{
//    for(int n=0; n<cellNumber.x; n++)  if(loopNumber==100)std::cerr<<"Personen in Zeile 1,"<<n<<": "<<pAllCells[1][n]<<std::endl;
    loopNumber++;
}

void ClStatistic::doCalculation()
{
    for(int m = 0; m<cellNumber.y; m++)
    {
        for(int n=0; n<cellNumber.x; n++)
        {
            pAllCells[m][n] = (int)(pAllCells[m][n]/loopNumber);
        }
    }
}
