
#ifndef CROWD_HPP_INCLUDED
#define CROWD_HPP_INCLUDED

#include "Area.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "HeatMap.hpp"
#include "People.hpp"

class ClCrowd
{
public:
    ClCrowd(float radius, ClArea * pArea, sf::Color Color, sf::Vector2f position, int numOfPeoples, ClHeatMap * pHeatMap);
    ~ClCrowd();

    void Update(sf::Vector2i position,float frameTime);
    void Update(float frameTime);
    void Draw(sf::RenderWindow& window);

    const sf::Vector2f  getMassPoint();
    float getRadius();

private:

    void Vec2DNormalize( sf::Vector2f *NormalizeMe );
    sf::Vector2f Seek(sf::Vector2f TargetPos, const sf::Vector2f & Destination, const sf::Vector2f & CurVelocity);

    ClArea *pArea;       // used for human - static object collision detection
                         // just registers the crowd there
    ClHeatMap *pHeatMap; // used for human - human collision detection

    std::vector<StrPeople *> peoples;
    sf::Vector2f position;
    float radius;

    // for debugging puposes : each Crowd does have a unique color
    sf::Color Color;

};

#endif // CROWD2_HPP_INCLUDED
