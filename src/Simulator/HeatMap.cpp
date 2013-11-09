#include "../../include/Simulator/HeatMap.hpp"

ClHeatMap::ClHeatMap(const sf::Vector2<int> &cellNumber, const sf::Vector2i &MapSize, ClArea *pArea, ClStatistic *pStatistic, ClDiagramm *pDiagramm)
{
    this->pArea = pArea;
    this->MapSize = MapSize;
    this->cellNumber = cellNumber;
    this->pStatistic = pStatistic;
    this->pDiagramm = pDiagramm;
    cellSize.x = MapSize.x / cellNumber.x;
    cellSize.y = MapSize.y / cellNumber.y;
    /// create the storage for all peoples in game
    for(int n=0; n< cellNumber.x *cellNumber.y; n++)
    {
        std::vector<StrPeople *> oneCell;
        SortedPeoples.push_back(oneCell);
    }
    pStatistic->planHeatMapStatistic(cellNumber, cellSize, sw_green, sw_yellow, sw_red);
    actualTime = 0;
    panicClock.restart();
}

ClHeatMap::~ClHeatMap() {}

void ClHeatMap::registerCrowd(const std::vector<StrPeople *> &Crowd)
{
    // Adds the peoples of a crowd to a local array where they can be managed all together
    for (unsigned int n=0; n<Crowd.size(); n++)
    {
        sf::Vector2f position = Crowd[n]->position[(PEOPLE_POSITION_MEMORY - 1)];
        position.x -= (int)position.x % (int)cellSize.x;
        position.y -= (int)position.y % (int)cellSize.y;
        if ( position.x > 0 && position.y > 0 && position.x <= MapSize.x && position.y <= MapSize.y )
        {
            SortedPeoples[(position.x / cellSize.x) + (position.y / cellSize.y)*cellNumber.x].push_back(Crowd[n]);
        }
    }
}

void ClHeatMap::draw(sf::RenderWindow& window)
{
    for (int x = 0; x < cellNumber.x; x++)
    {
        for (int y = 0; y < cellNumber.y; y++)
        {
            int cellCounter = x+y*cellNumber.x;
            int numberOfPeopleInCell = this->SortedPeoples[cellCounter].size();
            if(numberOfPeopleInCell >= sw_green)
            {
                pStatistic->rememberCells(x, y, numberOfPeopleInCell);
                if(doDraw==true)
                {
                    sf::RectangleShape colorCell(cellSize);
                    colorCell.setPosition(x*cellSize.x, y*cellSize.y);
                    colorCell.setFillColor(getColor(numberOfPeopleInCell));
                    window.draw(colorCell);
                }
            }
        }
    }
    pStatistic->rememberLoop();
}

void ClHeatMap::update(float frameTime)
{
    actualTime = panicClock.getElapsedTime().asSeconds();
    if(actualTime > 3.0) panicClock.restart();
    //loop through the SortedPeople vector to update the colored cells
    sf::Rect<float> Cell;
    for(unsigned int m=0; m<SortedPeoples.size(); m++)
    {
        Cell.top = ((int)(m/cellNumber.x))*cellSize.y;
        Cell.left = (m%cellNumber.x)*cellSize.x;
        Cell.height = cellSize.y;
        Cell.width = cellSize.x;

        for(unsigned int n=0; n<SortedPeoples[m].size(); n++)
        {
            // SortedPeoples[m][n]
            // cell number m
            // person number n
            if(!Cell.contains(SortedPeoples[m][n]->position[(PEOPLE_POSITION_MEMORY - 1)]))
            {
                if (SortedPeoples[m][n]->position[(PEOPLE_POSITION_MEMORY - 1)].x > 0
                        && SortedPeoples[m][n]->position[(PEOPLE_POSITION_MEMORY - 1)].y > 0
                        && SortedPeoples[m][n]->position[(PEOPLE_POSITION_MEMORY - 1)].x <= MapSize.x
                        && SortedPeoples[m][n]->position[(PEOPLE_POSITION_MEMORY - 1)].y <= MapSize.y)
                {
                    SortedPeoples[(int)(SortedPeoples[m][n]->position[(PEOPLE_POSITION_MEMORY - 1)].x / cellSize.x)
                                  + (int)(SortedPeoples[m][n]->position[(PEOPLE_POSITION_MEMORY - 1)].y / cellSize.y)
                                  * cellNumber.x].push_back(SortedPeoples[m][n]);
                    SortedPeoples[m].erase(SortedPeoples[m].begin()+n);
                }
            }
        }
    }

    // calculate distance force
    // 1. loop through the cells
    // 2. loop through every single people inside
    // 3. loop through to the neibour zones and the zone containing the guy
    // 4. calculate collision detection
    // 4.1 does the person leave the Area ?
    // 4.2 is the person hurt by fire ?

    // 1
    sf::Vector2f force;
    sf::Vector2f source;

    for (int x = 0; x < cellNumber.x ; x++)
    {
        for (int y = 0; y < cellNumber.y; y++)
        {
            //2.
            if(this->SortedPeoples[x+y*cellNumber.x].size() > 0)
            {
                for (unsigned int n = 0; n < SortedPeoples[x+y*cellNumber.x].size(); n++)
                {
                    //3.
                    // center
                    force = distanceForce(SortedPeoples[x+y*cellNumber.x],          SortedPeoples[x+y*cellNumber.x][n],n);

                    // top left
                    if( (x-1) >= 0 && (y-1) > 0 ) // does top left cell exist ?
                        force += distanceForce(SortedPeoples[(x-1)+(y-1)*cellNumber.x], SortedPeoples[x+y*cellNumber.x][n],-1);
                    // top cell
                    if ( (y-1) >= 0)
                        force += distanceForce(SortedPeoples[x+(y-1)*cellNumber.x],     SortedPeoples[x+y*cellNumber.x][n],-1);
                    // top right cell
                    if ((x+1) <= cellSize.x && (y-1) > 0)
                        force += distanceForce(SortedPeoples[(x+1)+(y-1)*cellNumber.x], SortedPeoples[x+y*cellNumber.x][n],-1);
                    // left cell
                    if ((x-1) >= 0 )
                        force += distanceForce(SortedPeoples[(x-1)+y*cellNumber.x],     SortedPeoples[x+y*cellNumber.x][n],-1);
                    // right cell
                    if ((x+1) <= cellSize.x )
                        force += distanceForce(SortedPeoples[(x+1)+y*cellNumber.x],     SortedPeoples[x+y*cellNumber.x][n],-1);
                    // bottom left cell
                    if ((x-1)>=0 && (y+1)<=cellSize.y)
                        force += distanceForce(SortedPeoples[(x-1)+(y+1)*cellNumber.x], SortedPeoples[x+y*cellNumber.x][n],-1);
                    // bottom cell
                    if ((y+1)<= cellSize.y)
                        force += distanceForce(SortedPeoples[x+(y+1)*cellNumber.x],    SortedPeoples[x+y*cellNumber.x][n],-1);
                    // bottom right cell
                    if ((y+1)<= cellSize.y&& (x+1)<=cellSize.x)
                        force += distanceForce(SortedPeoples[(x+1)+(y+1)*cellNumber.x], SortedPeoples[x+y*cellNumber.x][n],-1);


                    Vec2DNormalize(&force);
                    force.x *= -0.25*frameTime;
                    force.y *= -0.25*frameTime;
                    SortedPeoples[x+y*cellNumber.x][n]->force += force;



                }

            }
        }
    }
    additionalCellChecks();
}

void ClHeatMap::additionalCellChecks()
{
    int id = -1; // used for collision detection

    for (int x = 0; x < cellNumber.x ; x++)
    {
        for (int y = 0; y < cellNumber.y; y++)
        {
            //2.
            if(this->SortedPeoples[x+y*cellNumber.x].size() > 0)
            {
                for (unsigned int n = 0; n < SortedPeoples[x+y*cellNumber.x].size(); n++)
                {

                    // check collision
                    // 4.

                    id = pArea->getIdByVector(SortedPeoples[x+y*cellNumber.x][n]->position[(PEOPLE_POSITION_MEMORY - 1)]
                                               + SortedPeoples[x+y*cellNumber.x][n]->force );

                    if( id == -1)
                    {
                        SortedPeoples[x+y*cellNumber.x][n]->position[(PEOPLE_POSITION_MEMORY - 1)].x +=  SortedPeoples[x+y*cellNumber.x][n]->force.x ;
                        SortedPeoples[x+y*cellNumber.x][n]->position[(PEOPLE_POSITION_MEMORY - 1)].y +=  SortedPeoples[x+y*cellNumber.x][n]->force.y ;
                    }
                    else
                    {
                        // 4.1
                        // check for GATE
                        if (pArea->getType(id)==GATE) // collision with exit
                        {
                            SortedPeoples[x+y*cellNumber.x][n]->alive = false;
                            // erase from Heatmap ( crowd does a cleanup immediatly )
                            SortedPeoples[x+y*cellNumber.x].erase(SortedPeoples[x+y*cellNumber.x].begin()+n);
                        }
                        // 4.2 check for burning building
                        if (pArea->getOnFire(id) && this->actualTime > 3)
                        {
                             SortedPeoples[x+y*cellNumber.x][n]->alive = false;
                             // erase from Heatmap ( crowd does a cleanup immediatly )
                             SortedPeoples[x+y*cellNumber.x].erase(SortedPeoples[x+y*cellNumber.x].begin()+n);
                        }
                    }
            }
            }
        }
    }
}


sf::Vector2f ClHeatMap::distanceForce(std::vector<StrPeople *> &cell, StrPeople *checkMe, int position )
{
    sf::Vector2f force(0,0);
    sf::Vector2f delta;
    float helpVar;
    int NbCount = 0;

    for ( unsigned int n = 0; n< cell.size(); n++)
    {
        if ( position != n)
        {
            delta.x =   (checkMe->position[(PEOPLE_POSITION_MEMORY - 1)].x
                         - cell[n]->position[(PEOPLE_POSITION_MEMORY - 1)].x );
            delta.y =   (checkMe->position[(PEOPLE_POSITION_MEMORY - 1)].y
                         - cell[n]->position[(PEOPLE_POSITION_MEMORY - 1)].y );

            if (((delta.x*delta.x) + (delta.y * delta.y)) < 160) // is in range ?
            {
                helpVar = FSquare.getSqrt((int)((delta.x*delta.x) + (delta.y * delta.y)));
                Vec2DNormalize(&delta);
                helpVar = invert(FSquare.getSqrt(160),helpVar);
                force.x += delta.x *helpVar;
                force.y += delta.y *helpVar;
                NbCount++;
                if(actualTime > 3.0)
                {
                    if(checkMe->panic==true)
                    {
                        cell[n]->panic = true;
                    }
                }
            }
        }
    }

    Vec2DNormalize(&force);
    if (NbCount <= 1)
    {
        return sf::Vector2f (0,0);
    }

    return -force;
}

void ClHeatMap::toggleDraw()
{
    if (doDraw)
    {
        doDraw = false;
    }
    else doDraw = true;
}

//Calculates the Color that fits to the number of people in the current Cell
bool ClHeatMap::doDraw = false;

sf::Color ClHeatMap::getColor(int People)
{
    sf::Color background;
    background.b = 0;

    if (People <= sw_green)   // green 0,255,0
    {
        background.r = 0;
        background.g = 255;
        return background;
    }
    else if (People <= sw_yellow)   // at the end: yellow 255,255,0
    {
        background.r = (int)(((People-sw_green)/(sw_yellow-sw_green))*255);
        background.g = 255;
        return background;
    }
    background.r = 225;   // at the end: red 255,0,0
    if(People <= sw_red)
    {
        background.g = (int)(255-(((People-sw_yellow)/(sw_red-sw_yellow))*255));
    }
    else background.g = 0;
    return background;
}

float ClHeatMap::invert(float Max, float Current)
{
    return abs(Current - Max);
}

void ClHeatMap::Vec2DNormalize( sf::Vector2f *NormalizeMe )
{
    if (NormalizeMe->x != 0 && NormalizeMe->y != 0)
    {

        float helpVar = fabs(NormalizeMe->x) + fabs(NormalizeMe->y);
        NormalizeMe->x /= helpVar;
        NormalizeMe->y /= helpVar;
    }
}

// returns the ammount of casualties
int ClHeatMap::explosion(const sf::Vector2f &here, int explosionRadius)
{
    // 1. calculate the cell the explosion is hapenning in
    // 2. check for casualties in explosion cell and the neighbour cells and kill them ( alive = false )
    // 3. remove casualties from list ( Crowd cleans them up )
    // 4. return number of casualties

    sf::Vector2i explosion; // Coordinates of the cell containing the bomb
    int casualties = 0;

    // 1.
    explosion.x = here.x / cellSize.x;
    explosion.y = (here.y / cellSize.y );

    //2.
    // center cell
    casualties = calculateCasualtiesInCell(explosion, here, explosionRadius);

    // top-left cell
    explosion.y -= 1;
    explosion.x -= 1;
    if (explosion.y >= 0 && explosion.x >= 0)
        casualties += calculateCasualtiesInCell(explosion, here, explosionRadius);

    // left cell
    explosion.y += 1;
    if (explosion.x >= 0)
        casualties += calculateCasualtiesInCell(explosion, here, explosionRadius);

    // bottom-left cell
    explosion.y += 1;
    if (explosion.y < cellSize.y)
        casualties += calculateCasualtiesInCell(explosion, here, explosionRadius);
    // bottom cell
    explosion.x += 1;
    if (explosion.y < cellSize.y)
        casualties += calculateCasualtiesInCell(explosion, here, explosionRadius);
    // bottom-right cell
    explosion.x += 1;
    if (explosion.y < cellSize.y && explosion.x < cellSize.x)
        casualties += calculateCasualtiesInCell(explosion, here, explosionRadius);
    // right cell
    explosion.y -= 1;
    if ( explosion.x < cellSize.x)
        casualties += calculateCasualtiesInCell(explosion, here, explosionRadius);
    // top right cell
    explosion.y -= 1;
    if(explosion.y >= 0)
        casualties += calculateCasualtiesInCell(explosion, here, explosionRadius);
    // top cell
    explosion.x -= 1;
    if(explosion.y >= 0)
        casualties += calculateCasualtiesInCell(explosion, here, explosionRadius);

    return casualties;
}

// returns ammount of casualties (helper function of explosion)
int ClHeatMap::calculateCasualtiesInCell(const sf::Vector2i &cell, const sf::Vector2f &bombPosition, int explosionRadius)
{
    // 1. check wheather casualties are in range
    // 2. remove casualties from list ( alive = false -> Crowd cleans them up )
    // 3. return number of casualties

    int casualties = 0;
    sf::Vector2f position;

    for ( int n = 0; n < SortedPeoples[cell.x+cell.y*cellNumber.x].size(); n++)
    {
        // 1.
        position = SortedPeoples[cell.x+cell.y*cellNumber.x][n]->position[(PEOPLE_POSITION_MEMORY - 1)];
        if (FSquare.getSqrt((position.x - bombPosition.x)*(position.x - bombPosition.x) + (position.y - bombPosition.y)*(position.y - bombPosition.y)) < explosionRadius )
        {
            //2.
            SortedPeoples[cell.x+cell.y*cellNumber.x][n]->alive = false;
            SortedPeoples[cell.x+cell.y*cellNumber.x].erase(SortedPeoples[cell.x+cell.y*cellNumber.x].begin()+n);

            casualties++;
            pDiagramm->registerCasualties();
        }
    }
    //3.
    return casualties;
}
