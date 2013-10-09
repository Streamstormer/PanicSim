#ifndef HEATMAP_HPP_INCLUDED
#define HEATMAP_HPP_INCLUDED

#include "Crowd.hpp"
#include <Vector>

class ClHeatMap
{
public:
    ClHeatMap(const sf::Vector2<int> &cellNumber, const sf::Vector2i &MapSize)
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
    ~ClHeatMap() {}
    void registerCrowd(ClCrowd *Crowd)
    {
        // Adds the peoples of a crowd to a local array where they can be managed all together
        const std::vector<StrPeople *> registerMe = Crowd->getPeoples();
        for (unsigned int n=0; n<registerMe.size(); n++)
        {
            sf::Vector2f position = registerMe[n]->position;
            position.x -= (int)position.x % (int)cellSize.x;
            position.y -= (int)position.y % (int)cellSize.y;
            // needs to be improved
            if ( position.x > 0 && position.y > 0 && position.x < 800 && position.y < 600 )
            {
                SortedPeoples[(position.x / cellSize.x) + (position.y / cellSize.y)*cellNumber.x].push_back(registerMe[n]);
            }
        }
    }

    void draw(sf::RenderWindow& window)
    {
     //   if(doDraw==true)
        if(false)
        {
        sf::RectangleShape colorCell(cellSize);
        for (int x = 0; x < cellNumber.x ; x++)
        {
            for (int y = 0; y < cellNumber.y; y++)
            {
                colorCell.setPosition(x*cellSize.x, y*cellSize.y);
                colorCell.setFillColor(getColor(this->SortedPeoples[x+y*cellNumber.x].size()));
                window.draw(colorCell);
            }
        }
        }
    }

    void update()
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
                    if ( SortedPeoples[m][n]->position.x > 0 && SortedPeoples[m][n]->position.y > 0 && SortedPeoples[m][n]->position.x < 800 && SortedPeoples[m][n]->position.y < 600 )
                    {
                        SortedPeoples[(int)(SortedPeoples[m][n]->position.x / cellSize.x) + (int)(SortedPeoples[m][n]->position.y / cellSize.y)*cellNumber.x].push_back(SortedPeoples[m][n]);
                    }
                    SortedPeoples[m].erase(SortedPeoples[m].begin()+n);
                }
            }
        }
    }

    static void toggleDraw()
    {
   /*     if (doDraw)
        {
            doDraw = false;
        }
        else doDraw = true; */
    }

private:
    //Calculates the Color that fits to the number of people in the current Cell
 //   static bool doDraw ;

    sf::Color getColor(int People)
    {
        sf::Color background;
        background.b = 0;
        if(People == 0)  //black 0,0,0
        {
            background.r = 0;
            background.g = 0;
            return background; // No People -> Transparent Color
        }
        else if (People <= 3)   // at the end: green 0,255,0
        {
            background.r = 0;
            background.g = (People/3)*255;
            return background;
        }
        else if (People <= 6)   // at the end: yellow 255,255,0
        {
            background.r = ((People-3)/3)*255;
            background.g = 255;
            return background;
        }
        background.r = 225;   // at the end: red 255,0,0
        if(People<=9){
            background.g = 255-(((People-6)/3)*255);
        }else background.g = 0;
        return background;

    }
    std::vector<std::vector<StrPeople *> > SortedPeoples ;
    sf::Vector2i cellNumber;
    sf::Vector2i MapSize;
    sf::Vector2f cellSize;
};
// bool ClHeatMap::doDraw = false;

#endif // HEATMAP_HPP_INCLUDED
