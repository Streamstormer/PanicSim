#include "../../include/Simulator/HeatMap.hpp"

ClHeatMap::ClHeatMap(const sf::Vector2<int> &cellNumber, const sf::Vector2i &MapSize)
{
    this->MapSize = MapSize;
    this->cellNumber = cellNumber;
    cellSize.x = MapSize.x / cellNumber.x;
    cellSize.y = MapSize.y / cellNumber.y;
    /// create the storage for all peoples in game
    for(int n=0; n< cellNumber.x *cellNumber.y; n++)
    {
        std::vector<StrPeople *> oneCell;
        SortedPeoples.push_back(oneCell);
    }
}
ClHeatMap::~ClHeatMap() {}
void ClHeatMap::registerCrowd(const std::vector<StrPeople *> &Crowd)
{
    // Adds the peoples of a crowd to a local array where they can be managed all together
    for (unsigned int n=0; n<Crowd.size(); n++)
    {
        sf::Vector2f position = Crowd[n]->position;
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
    if(doDraw==true)
    {
        sf::RectangleShape colorCell(cellSize);
        for (int x = 0; x < cellNumber.x ; x++)
        {
            for (int y = 0; y < cellNumber.y; y++)
            {
                if(this->SortedPeoples[x+y*cellNumber.x].size() > 0)
                {
                colorCell.setPosition(x*cellSize.x, y*cellSize.y);
                colorCell.setFillColor(getColor(this->SortedPeoples[x+y*cellNumber.x].size()));
                window.draw(colorCell);
                }
            }
        }
    }
}

void ClHeatMap::update(float frameTime)
{
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
            // SortedPeoples[m][n] cell number m
            // person number n
            if(!Cell.contains(SortedPeoples[m][n]->position))
            {
                if ( SortedPeoples[m][n]->position.x > 0 && SortedPeoples[m][n]->position.y > 0 && SortedPeoples[m][n]->position.x <= MapSize.x && SortedPeoples[m][n]->position.y <= MapSize.y )
                {
                    SortedPeoples[(int)(SortedPeoples[m][n]->position.x / cellSize.x) + (int)(SortedPeoples[m][n]->position.y / cellSize.y)*cellNumber.x].push_back(SortedPeoples[m][n]);
                }
                SortedPeoples[m].erase(SortedPeoples[m].begin()+n);
            }
        }
    }

    // calculate distance force
    // 1. loop through the cells
    // 2. loop through every single people inside
    // 3. loop through to the neibour zones and the zone containing the guy
    // 1
    sf::Vector2f force;

    for (int x = 0; x < cellNumber.x ; x++)
        {
            for (int y = 0; y < cellNumber.y; y++)
            {
                //2.
                if(this->SortedPeoples[x+y*cellNumber.x].size() > 0)
                {
                    for (unsigned int n = 0; n < SortedPeoples[x+y*cellNumber.x].size();n++)
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
                    force.x *= -0.25;
                    force.y *= -0.25;

                    SortedPeoples[x+y*cellNumber.x][n]->position += force*frameTime;

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
            delta.x =   (checkMe->position.x-cell[n]->position.x );
            delta.y =   (checkMe->position.y-cell[n]->position.y );

            if (((delta.x*delta.x) + (delta.y * delta.y)) < 160) // is in range ?
            {
                helpVar = sqrt((delta.x*delta.x) + (delta.y * delta.y));
                Vec2DNormalize(&delta);
                helpVar = invert(sqrt(160),helpVar);

                force.x += delta.x *helpVar;
                force.y += delta.y *helpVar;
                NbCount++;
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

    if (People <= sw_green)   // at the end: green 0,255,0
    {
        background.r = 0;
        background.g = (int)((People/sw_green)*255);
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
