#ifndef HEATMAP_HPP_INCLUDED
#define HEATMAP_HPP_INCLUDED

#include "Crowd.hpp"
#include <vector>

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
        for(int n=0;n< cellNumber.x *cellNumber.y; n++)
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
        for (int n=0;n<registerMe.size();n++)
        {
            sf::Vector2f position = registerMe[n]->position;
            position.x -= (int)position.x % (int)cellSize.x;
            position.y -= (int)position.y % (int)cellSize.y;
            // needs to be improved
            if ( position.x > 0 && position.y > 0 && position.x < 800 && position.y < 600 ) SortedPeoples[(position.x / cellSize.x) + (position.y / cellSize.y)*cellNumber.x].push_back(registerMe[n]);
        }
    }
    void draw(sf::RenderWindow& window)
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



    private:
    //Calculates the Color that fits to the number of people in the current Cell
    // needs rework to look cool
    sf::Color getColor(int People)
    {
        if(People == 0)
        {
            return sf::Color::Transparent; // No People -> Transparent Color
        }
        else if (People < 3)
        {
            return sf::Color::Green;
        }
        else if (People < 7)
        {
            return sf::Color::Yellow;
        }
        return sf::Color::Red;

    }
        std::vector<std::vector<StrPeople *> > SortedPeoples ;
        sf::Vector2i cellNumber;
        sf::Vector2i MapSize;
        sf::Vector2f cellSize;
};

#endif // HEATMAP_HPP_INCLUDED
