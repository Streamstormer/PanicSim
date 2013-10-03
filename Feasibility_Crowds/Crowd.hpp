
#ifndef CROWD_HPP_INCLUDED
#define CROWD_HPP_INCLUDED
#include "Area.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <math.h>
#define MAXPPL 500
#define MAXSPEED 0.1f

struct StrPeople
{
    sf::Vector2f position;
    sf::Vector2f forceVec;
};

class ClCrowd
{
public:
    ClCrowd(float radius, ClArea * area);
    ~ClCrowd();

    void update(sf::Vector2i position,float frameTime);

    void draw(sf::RenderWindow& window);

    const sf::Vector2f  getMassPoint();
    float getRadius();
private:


    void Vec2DNormalize( sf::Vector2f *NormalizeMe );
    sf::Vector2f Seek(sf::Vector2f TargetPos, const sf::Vector2f & Destination, const sf::Vector2f & CurVelocity);
    float invert(float Max, float Current);
    sf::Vector2f DistanceForce(StrPeople* start,  int current);
    //sf::Vector2f Cohesion(StrPeople* start, const sf::Vector2f & massPoint, int current);

    ClArea *Area; // used for collision detection
    struct StrPeople peoples[MAXPPL];
    sf::Vector2f position;
    float radius;


};

#endif // CROWD2_HPP_INCLUDED
