#include "../../include/Simulator/Statistic.hpp"
bool ClStatistic::doDrawAverage = false;

ClStatistic::ClStatistic()
{
    numberBomb = 0;
    numberFire = 0;
    numberKillsFire = 0;
    numberKillsBomb = 0;
}

ClStatistic::~ClStatistic()
{
    delete pAllCells;
}

void ClStatistic::planHeatMapStatistic(sf::Vector2i cellNumber, sf::Vector2f cellSize, const int sw_green, const int sw_yellow, const int sw_red)
{
    this->cellNumber = cellNumber;
    this->cellSize  = cellSize;
    this->sw_green = sw_green;
    this->sw_yellow = sw_yellow;
    this->sw_red = sw_red;
    loopNumber = 0;

    pAllCells = new int*[cellNumber.y];
    pDrawCells = new int*[cellNumber.y];
    for(int y=0; y < cellNumber.y; y++)
    {
        pAllCells[y] = new int[cellNumber.x];
        pDrawCells[y] = new int[cellNumber.x];
    }

    for(int y=0; y<cellNumber.y; y++)
    {
        for(int x=0; x<cellNumber.x; x++)
        {
            pAllCells[y][x] = 0;
            pDrawCells[y][x] = 0;
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

void ClStatistic::draw(sf::RenderWindow &window)
{
    if(doDrawAverage==true)
    {
        for(int m = 0; m<cellNumber.y; m++)
        {
            for(int n=0; n<cellNumber.x; n++)
            {
                int people = pDrawCells[m][n];
                if(people >= sw_green)
                {
                    sf::RectangleShape colorCell(cellSize);
                    colorCell.setPosition(n*cellSize.x, m*cellSize.y);
                    colorCell.setFillColor(getColor(people));
                    window.draw(colorCell);
                }
            }
        }
    }
    /*
        std::cerr<<"activated bombs: "<<numberBomb<<std::endl;
        std::cerr<<"activated fires: "<<numberFire<<std::endl;
        std::cerr<<"killed by fire:"<<numberKillsFire<< std::endl;
        std::cerr<<"killed by bomb:"<<numberKillsBomb<< std::endl;
    */
}

sf::Color ClStatistic::getColor(int people)
{
    sf::Color background;
    background.b = 0;

    if (people <= sw_green)   // at the end: green 0,255,0
    {
        background.r = 0;
        background.g = (int)((people/sw_green)*255);
        return background;
    }
    else if (people <= sw_yellow)   // at the end: yellow 255,255,0
    {
        background.r = (int)(((people-sw_green)/(sw_yellow-sw_green))*255);
        background.g = 255;
        return background;
    }
    background.r = 225;   // at the end: red 255,0,0
    if(people <= sw_red)
    {
        background.g = (int)(255-(((people-sw_yellow)/(sw_red-sw_yellow))*255));
    }
    else background.g = 0;
    return background;
}

/*
void ClStatistic::toggleAverageDraw()
{
    if (doDrawAverage==true)
    {
        doDrawAverage = false;
    }
    else doDrawAverage = true;
}
*/

void ClStatistic::update()
{
    if(doDrawAverage==true)
    {
        for(int m = 0; m<cellNumber.y; m++)
        {
            for(int n=0; n<cellNumber.x; n++)
            {
                pDrawCells[m][n] = (int)(pAllCells[m][n] / loopNumber);
            }
        }
    }
}

void ClStatistic::rememberKills(int number, bool bomb)
{
    if(bomb)
    {
        numberKillsBomb += number;
    }
    else numberKillsFire += number;
}
