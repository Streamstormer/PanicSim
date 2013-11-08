/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    handling all statistic calculations (in HeatMap, by creation of threats, time for evacuation, number of casualties)
---------------------------------------------------------------------------------------------------------------------------------------
*/

#include "../../include/Simulator/Statistic.hpp"

bool ClStatistic::doDrawAverage = false;
bool ClStatistic::setStop = false;
bool ClStatistic::setStart = false;
bool ClStatistic::setPause = false;
bool ClStatistic::setContinue = false;
bool ClStatistic::setFast = false;
bool ClStatistic::setFaster = false;
int ClStatistic::numberBomb = 0;
int ClStatistic::numberFire = 0;
int ClStatistic::numberKillsFire = 0;
int ClStatistic::numberKillsBomb = 0;
int ClStatistic::time = 0;

ClStatistic::ClStatistic()
{
    startTime = 0;
    pauseTime = 0;
    fastTime = 0;
    fasterTime = 0;
    checkFast = false;
    checkFaster = false;
    checkPause = false;
}

ClStatistic::~ClStatistic()
{
    delete pAllCells;
    delete pDrawCells;
}

//basic ajustment for HeatMap calculations
void ClStatistic::planHeatMapStatistic(sf::Vector2i cellNumber, sf::Vector2f cellSize, const int sw_green, const int sw_yellow, const int sw_red)
{
    //1. initialising of all variables
    //2. initialising of cells for calculation and for drawing

    //1.
    this->cellNumber = cellNumber;
    this->cellSize  = cellSize;
    this->sw_green = sw_green;
    this->sw_yellow = sw_yellow;
    this->sw_red = sw_red;
    loopNumber = 0;

    //2.
    pAllCells = new int*[cellNumber.y];
    pDrawCells = new int*[cellNumber.y];
    pRedCells = new int*[cellNumber.y];
    for(int y=0; y < cellNumber.y; y++)
    {
        pAllCells[y] = new int[cellNumber.x];
        pDrawCells[y] = new int[cellNumber.x];
        pRedCells[y] = new int[cellNumber.x];
    }

    for(int y=0; y<cellNumber.y; y++)
    {
        for(int x=0; x<cellNumber.x; x++)
        {
            pAllCells[y][x] = 0;
            pDrawCells[y][x] = 0;
            pRedCells[y][x] = 0;
        }
    }
}

//recognize the cell with more than sw_green people (save in AllCells)
void ClStatistic::rememberCells(int cellX, int cellY, const int numberOfPeople)
{
    //remember Cells only after the first 3 seconds after start of simulation
    float hMtime = startClock.getElapsedTime().asSeconds();
    if(hMtime>3)
    {
        //if the averageHeatMap is not drawn
        if(doDrawAverage==false)
        {
            //count number of people in this cell
            pAllCells[cellY][cellX] += numberOfPeople;
            //if red cell - remember for later statistic
            if(numberOfPeople>=sw_red)
            {
                rememberRedCell(cellX, cellY);
            }
        }
    }
}

void ClStatistic::rememberRedCell(int x, int y)
{
    pRedCells[y][x] += 1;
}

//incrememts number of loops in which cells are updated (if the average HeatMap is not drawn)
void ClStatistic::rememberLoop()
{
    if(doDrawAverage==false)
    {
        loopNumber++;
    }
}

//if a threat is acivated
void ClStatistic::rememberThreats(bool type_bomb, bool type_fire)
{
    if(doDrawAverage==false)
    {
        if(type_fire)
        {
            numberFire++;
        }

        if(type_bomb)
        {
            numberBomb++;
        }
    }
}

//draw average HeatMap
void ClStatistic::draw(sf::RenderWindow &window)
{
    //1. check if doDrawAverage is true
    //2. loop through all cells
    //3. get number of people by DrawCells (averaged AllCells)
    //4. if sw_green is reached -> draw cell

    //1.
    if(doDrawAverage==true)
    {
        //2.
        for(int m = 0; m<cellNumber.y; m++)
        {
            for(int n=0; n<cellNumber.x; n++)
            {
                //3.
                int people = pDrawCells[m][n];
                //4.
                if(people >= sw_green)
                {
                    sf::RectangleShape colorCell(cellSize);
                    colorCell.setPosition(n*cellSize.x, m*cellSize.y);
                    if(pRedCells[m][n]>100)
                    {
                        colorCell.setFillColor(getColor(sw_red));
                    } else colorCell.setFillColor(getColor(people));
                    window.draw(colorCell);
                }
            }
        }
    }
}

//calculate right color for drawing cells according to borders
sf::Color ClStatistic::getColor(int people)
{
    sf::Color background;
    background.b = 0;

    if (people == sw_green)   // at the end: green 0,255,0
    {
        background.r = 0;
        background.g = 255;
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

//setter for doDrawAverage
void ClStatistic::setAverageDraw(bool newBool)
{
    doDrawAverage=newBool;
}

//getter for doDrawAverage
bool ClStatistic::getAverageDraw()
{
    return doDrawAverage;
}

void ClStatistic::update()
{
    //1. if staistic is to be shown calculate average of allCells in drawCells

    // always check every possible time
    //2. if start of simulation (start clock)
    //3. if pause of simulation (pause clock)
    //4. if faster simulation (fast clock)
    //5. if (more) faster simulation (faster clock)
    //6. if continue simulation
    //7. if stop simulation (calculate real time)

    //1.
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

    //2.
    if(setStart)
    {
        setStart = false;
        startClock.restart();
    }

    //3.
    if(setPause)
    {
        if(checkPause==false)
        {
            setPause = false;
            checkPause = true;
            pauseClock.restart();
            if(checkFast)
            {
                fastTime += fastClock.getElapsedTime().asSeconds();
                checkFast = false;
            }
            if(checkFaster)
            {
                fasterTime += fasterClock.getElapsedTime().asSeconds();
                checkFaster = false;
            }
        }
    }

    //4.
    if(setFast)
    {
        setFast = false;
        checkFast = true;
        fastClock.restart();
        if(checkPause)
        {
            pauseTime += pauseClock.getElapsedTime().asSeconds();
            checkPause = false;
        }
        if(checkFaster)
        {
            fasterTime += fasterClock.getElapsedTime().asSeconds();
            checkFaster = false;
        }
    }

    //5.
    if(setFaster)
    {
        setFaster = false;
        checkFaster = true;
        fasterClock.restart();
        if(checkFast)
        {
            fastTime += fastClock.getElapsedTime().asSeconds();
            checkFast = false;
        }
        if(checkPause)
        {
            pauseTime += pauseClock.getElapsedTime().asSeconds();
            checkPause = false;
        }
    }

    //6.
    if(setContinue)
    {
        setContinue = false;
        if(checkPause)
        {
            pauseTime += pauseClock.getElapsedTime().asSeconds();
            checkPause = false;
        }
        if(checkFast)
        {
            fastTime += fastClock.getElapsedTime().asSeconds();
            checkFast = false;
        }
        if(checkFaster)
        {
            fasterTime += fasterClock.getElapsedTime().asSeconds();
            checkFaster = false;
        }
    }

    //7.
    if(setStop)
    {
        setStop = false;
        startTime = startClock.getElapsedTime().asSeconds();
        if(checkPause)
        {
            pauseTime += pauseClock.getElapsedTime().asSeconds();
            checkPause = false;
        }
        if(checkFast)
        {
            fastTime += fastClock.getElapsedTime().asSeconds();
            checkFast = false;
        }
        if(checkFaster)
        {
            fasterTime += fasterClock.getElapsedTime().asSeconds();
            checkFaster = false;
        }

        if(pauseTime>0||fastTime>0||fasterTime>0)
        {
            if(pauseTime>0)
            {
                startTime -= pauseTime;
            }
            if(fastTime>0)
            {
                startTime += fastTime;
            }
            if(fasterTime>0)
            {
                startTime += 2*fasterTime;
            }
        }
        time = (int) startTime;
    }
}

//recognize all casualties if average draw is not shown (differentiation between bombs and fire)
void ClStatistic::rememberKills(int number, bool bomb)
{
    if(doDrawAverage==false)
    {
        if(bomb)
        {
            numberKillsBomb += number;
        }
        else numberKillsFire += number;
    }
}

//setter for setStart
void ClStatistic::startTimer()
{
    setStart = true;
}

//setter for setStop
void ClStatistic::rememberTime()
{
    setStop = true;
}

//setter for setPause
void ClStatistic::rememberPause()
{
    setPause = true;
}

//setter for setContinue
void ClStatistic::rememberContinue()
{
    setContinue = true;
}

//setter for setFast
void ClStatistic::rememberFast()
{
    setFast = true;
}

//setter for setFaster
void ClStatistic::rememberFaster()
{
    setFaster = true;
}

//getter for number of bombs
int* ClStatistic::getNumberBomb()
{
    return &numberBomb;
}

//getter for number of fire
int* ClStatistic::getNumberFire()
{
    return &numberFire;
}

//getter for number of casualties (fire)
int* ClStatistic::getNumberKillsFire()
{
    return &numberKillsFire;
}

//getter for number of casualties (bomb)
int* ClStatistic::getNumberKillsBomb()
{
    return &numberKillsBomb;
}

//getter for evacuation time
int* ClStatistic::getTime()
{
    return &time;
}
