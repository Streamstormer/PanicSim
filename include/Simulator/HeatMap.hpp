#ifndef HEATMAP_HPP_INCLUDED
#define HEATMAP_HPP_INCLUDED

#include <math.h>
#include <vector>
#include "People.hpp"

class ClHeatMap
{
public:
    ClHeatMap(const sf::Vector2<int> &cellNumber, const sf::Vector2i &MapSize);
    ~ClHeatMap();
    void registerCrowd(const std::vector<StrPeople *> &Crowd);
    void draw(sf::RenderWindow& window);
    void update(float frameTime);
    static void toggleDraw();
    static bool doDraw;

    // for collision detection between single humans
    // const std::vector<StrPeople *> & getCell(sf::Vector2f, bool top, bool right, bool center)

private:
    sf::Vector2f distanceForce(std::vector<StrPeople *> &cell, StrPeople *checkMe, int position );
    void Vec2DNormalize( sf::Vector2f *NormalizeMe );
    float invert(float Max, float Current);

    std::vector<std::vector<StrPeople *> > SortedPeoples ;
    sf::Vector2i cellNumber;
    sf::Vector2i MapSize;
    sf::Vector2f cellSize;

    sf::Color getColor(int People);
    //used for giving the heatmap different collors depending on number of people
    //color is green until there are sw_green people
    const static int sw_green = 10;
    //color is yellow until there are sw_yellow people
    const static int sw_yellow = 17;
    //color is (stepwise) red until there are sw_red people above it´s red too
    const static int sw_red = 25;

};

#endif // HEATMAP_HPP_INCLUDED
