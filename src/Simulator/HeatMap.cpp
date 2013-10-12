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
void ClHeatMap::registerCrowd(ClCrowd *Crowd)
{
    // Adds the peoples of a crowd to a local array where they can be managed all together
    const std::vector<StrPeople *> registerMe = Crowd->getPeoples();
    for (unsigned int n=0; n<registerMe.size(); n++)
    {
        sf::Vector2f position = registerMe[n]->position;
        position.x -= (int)position.x % (int)cellSize.x;
        position.y -= (int)position.y % (int)cellSize.y;
        if ( position.x > 0 && position.y > 0 && position.x <= MapSize.x && position.y <= MapSize.y )
        {
            SortedPeoples[(position.x / cellSize.x) + (position.y / cellSize.y)*cellNumber.x].push_back(registerMe[n]);
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

void ClHeatMap::update()
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
