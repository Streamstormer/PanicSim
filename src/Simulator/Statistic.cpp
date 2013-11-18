/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    handling all statistic calculations (in HeatMap, by creation of threats, time for evacuation, number of casualties)
---------------------------------------------------------------------------------------------------------------------------------------
*/

#include "../../include/Simulator/Statistic.hpp"

bool ClStatistic::doDrawStatistic = false;
bool ClStatistic::doDrawDiagramm = false;
int ClStatistic::numberBomb = 0;
int ClStatistic::numberFire = 0;
int ClStatistic::numberKillsFire = 0;
int ClStatistic::numberKillsBomb = 0;
int ClStatistic::numberKillsPressure = 0;
int ClStatistic::numberCasualties = 0;
int ClStatistic::timeInSeconds = 0;
//start speed is normal (1)
int ClStatistic::speed = 1;

ClStatistic::ClStatistic(ClDiagramm *pDiagramm)
{
    this->pDiagramm = pDiagramm;
    time = 0;
    panic = false;
}

ClStatistic::~ClStatistic()
{
    delete pAllCells;
    delete pDrawCells;

    for(unsigned int n=0; n<casualtiePosition.size(); n++)
    {
        delete casualtiePosition[n];
    }
}

//basic ajustment for HeatMap calculations
void ClStatistic::planHeatMapStatistic(sf::Vector2i cellNumber, sf::Vector2f cellSize, const int sw_green, const int sw_yellow, const int sw_red)
{
    //1. initialising of all variables
    //2. initialising of cells for calculation and for drawing and set all cells to 0

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

//recognize the cell with more than sw_green people (save in AllCells)
void ClStatistic::rememberCells(int cellX, int cellY, const int numberOfPeople)
{
    //if the averageHeatMap is not drawn
    if(doDrawStatistic==false&&panic==true)
    {
        //count number of people in this cell
        pAllCells[cellY][cellX] += numberOfPeople;
    }
}

//incrememts number of loops in which cells are updated (if the average HeatMap is not drawn)
void ClStatistic::rememberLoop()
{
    if(doDrawStatistic==false&&panic==true)
    {
        loopNumber++;
    }
}

//if a threat is acivated
void ClStatistic::rememberThreats(bool type_bomb, bool type_fire)
{
    if(type_fire)
    {
        numberFire++;
        pDiagramm->registerFire();
    }
    if(type_bomb)
    {
        numberBomb++;
        pDiagramm->registerBomb();
    }

    if(panic==false)
    {
        panic=true;
    }
}

//draw average HeatMap
void ClStatistic::drawStatistic(sf::RenderWindow &window)
{
    //1. check if doDrawAverage is true
    //2. loop through all cells
    //3. get number of people by DrawCells (averaged AllCells)
    //4. if sw_green is reached -> draw cell

    //1.
    if(doDrawStatistic)
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
                    colorCell.setFillColor(getColor(people));
                    window.draw(colorCell);
                }
            }
        }

        // draw all death people and set every where a black point
        sf::CircleShape deathPoint;
        deathPoint.setFillColor(sf::Color::Black);
        deathPoint.setRadius(3);
        deathPoint.setOrigin(1.5, 1.5);

        for(unsigned int n=0; n<casualtiePosition.size(); n++)
        {
            deathPoint.setPosition(*casualtiePosition[n]);
            window.draw(deathPoint);
        }
    }
}

void ClStatistic::drawDiagramm(sf::RenderWindow &window)
{
    if(doDrawDiagramm)
    {
        //set position and size of diagramm
        sf::Vector2f di_position(DI_POSITION, DI_POSITION);
        sf::Vector2f di_size(DI_SIZE_X, DI_SIZE_Y);
        //draw diagramm at this position
        pDiagramm->draw(di_position, di_size.x, di_size.y, window);
    }
}

//calculate right color for drawing cells according to borders
sf::Color ClStatistic::getColor(int people)
{
    sf::Color background;
    background.b = 0;

    if (people == sw_green)   // green 0,255,0
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

//setter for doDrawStatistic
void ClStatistic::setDoDrawStatistic(bool newBool)
{
    doDrawStatistic=newBool;
}

//setter for doDrawDiagramm
void ClStatistic::toggleDiagrammDraw()
{
    if(doDrawDiagramm)
    {
        doDrawDiagramm = false;
    }else doDrawDiagramm = true;
}

void ClStatistic::update(float frameTime)
{
    this->frameTime = frameTime;
    //if statistic is to be shown calculate average of allCells in drawCells
    if(doDrawStatistic)
    {
        for(int m = 0; m<cellNumber.y; m++)
        {
            for(int n=0; n<cellNumber.x; n++)
            {
                if(!loopNumber>0) loopNumber=1;
                pDrawCells[m][n] = (int)(pAllCells[m][n] / loopNumber);
            }
        }
    }
    //if statistic is not drawn and panic has started - start timer
    if(doDrawStatistic==false && panic == true)
    {
        time += frameTime;
    }
    //calculate time as seconds
    timeInSeconds = time/1000;
}

//recognize all casualties if average draw is not shown (differentiation between bombs and fire)
void ClStatistic::rememberKills(int number, bool bomb, bool fire, bool pressure, sf::Vector2f position)
{
    if(bomb) numberKillsBomb += number;
    if(fire) numberKillsFire += number;
    if(pressure) numberKillsPressure += number;

    sf::Vector2f *newPosition = new sf::Vector2f(position.x, position.y);
    casualtiePosition.push_back(newPosition);

    // all casualties
    numberCasualties += number;
}

void ClStatistic::rememberSpeed(int newSpeed)
{
    speed = newSpeed;
}

void ClStatistic::reset()
{
    numberBomb = 0;
    numberFire = 0;
    numberCasualties = 0;
    numberKillsBomb = 0;
    numberKillsFire = 0;
    numberKillsPressure = 0;
    timeInSeconds = 0;
    speed = 1;
    doDrawDiagramm = false;
    doDrawStatistic = false;
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

//getter for number of casualties (pressure)
int* ClStatistic::getNumberKillsPressure()
{
    return &numberKillsPressure;
}

//getter for evacuation time
int* ClStatistic::getTime()
{
    return &timeInSeconds;
}

//getter for speed
int* ClStatistic::getSpeed()
{
    return &speed;
}

//getter for number of casualties
int* ClStatistic::getNumberCasualties()
{
    return &numberCasualties;
}
