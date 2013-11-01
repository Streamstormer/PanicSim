#ifndef HEATMAP_HPP_INCLUDED
#define HEATMAP_HPP_INCLUDED

#include <math.h>
#include <vector>
#include "People.hpp"
#include "FastSquareroot.hpp"
#include "Area.hpp"
#include "Statistic.hpp"

class ClHeatMap
{
public:
    ClHeatMap(const sf::Vector2<int> &cellNumber, const sf::Vector2i &MapSize, ClArea *pArea);
    ~ClHeatMap();
    void registerCrowd(const std::vector<StrPeople *> &Crowd);
    void draw(sf::RenderWindow& window);
    void update(float frameTime);
    static void toggleDraw();
    static bool doDraw;
private:
    sf::Vector2f distanceForce(std::vector<StrPeople *> &cell, StrPeople *checkMe, int position );
    void Vec2DNormalize( sf::Vector2f *NormalizeMe );
    float invert(float Max, float Current);

    ClArea *pArea;
    ClStatistic *pStatistic;

    std::vector<std::vector<StrPeople *> > SortedPeoples ;
    sf::Vector2i cellNumber;
    sf::Vector2i MapSize;
    sf::Vector2f cellSize;

    ClFastSquareroot FSquare; // used for faster squareroots than sqrt() of <math.h>

    sf::Color getColor(int People);
    //used for giving the heatmap different collors depending on number of people
    //color is green until there are sw_green people
    const static int sw_green = 3;
    //color is yellow until there are sw_yellow people
    const static int sw_yellow = 15;
    //color is (stepwise) red until there are sw_red people above it´s red too
    const static int sw_red = 25;

    sf::Clock checkStatClock;
    float statisticTime;
};

#endif // HEATMAP_HPP_INCLUDED
