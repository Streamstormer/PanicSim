
/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Lukas / Melanie
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    used for fast person - person force calculation
            && for collision detection
---------------------------------------------------------------------------------------------------------------------------------------
*/



#ifndef HEATMAP_HPP_INCLUDED
#define HEATMAP_HPP_INCLUDED

#include <math.h>
#include <vector>
#include "People.hpp"
#include "FastSquareroot.hpp"
#include "Area.hpp"
#include "Statistic.hpp"
#include "Diagramm.hpp"

class ClHeatMap
{
public:
    ClHeatMap(const sf::Vector2<int> &cellNumber, const sf::Vector2i &MapSize, ClArea *pArea, ClStatistic *pStatistic, ClDiagramm *pDiagramm);
    ~ClHeatMap();
    void registerCrowd(const std::vector<StrPeople *> &Crowd);
    void draw(sf::RenderWindow& window);
    void update(float frameTime);
    int explosion(const sf::Vector2f &here, int explosionRadius); // returns the ammount of casualties
    static void toggleDraw();

private:
    sf::Vector2f distanceForce(std::vector<StrPeople *> &cell, StrPeople *checkMe, int position );
    void additionalCellChecks();
    int calculateCasualtiesInCell(const sf::Vector2i &cell, const sf::Vector2f &bombPosition, int explosionRadius); // returns ammount of casualties (helper function of explosion)
    void Vec2DNormalize( sf::Vector2f *NormalizeMe );
    float invert(float Max, float Current);

    ClArea *pArea;
    ClStatistic *pStatistic;
    ClDiagramm *pDiagramm;

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

    const static int MAX_ACTUALTIME = 4000;

    int positonMemoryPosition;

    float actualTime;
    static bool doDraw;
};

#endif // HEATMAP_HPP_INCLUDED
