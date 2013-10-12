#ifndef HEATMAP_HPP_INCLUDED
#define HEATMAP_HPP_INCLUDED

#include "Crowd.hpp"
#include <vector>

class ClHeatMap
{
public:
    ClHeatMap(const sf::Vector2<int> &cellNumber, const sf::Vector2i &MapSize);
    ~ClHeatMap();
    void registerCrowd(ClCrowd *Crowd);
    void draw(sf::RenderWindow& window);
    void update();
    static void toggleDraw();
    static bool doDraw;

private:
    sf::Color getColor(int People);
    std::vector<std::vector<StrPeople *> > SortedPeoples ;
    sf::Vector2i cellNumber;
    sf::Vector2i MapSize;
    sf::Vector2f cellSize;

    //used for giving the heatmap different collors depending on number of people
    //color is green until there are sw_green people
    const static int sw_green = 5;
    //color is yellow until there are sw_yellow people
    const static int sw_yellow = 10;
    //color is (stepwise) red until there are sw_red people above it´s red too
    const static int sw_red = 15;

};

#endif // HEATMAP_HPP_INCLUDED
