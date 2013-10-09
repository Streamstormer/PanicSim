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

};

#endif // HEATMAP_HPP_INCLUDED
