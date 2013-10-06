
#ifndef CROWD_HPP_INCLUDED
#define CROWD_HPP_INCLUDED

#include "Area.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <Vector>

struct StrPeople
{
    sf::Vector2f position;
    sf::Vector2f forceVec;
};

class ClCrowd
{
public:
    ClCrowd(float radius, ClArea * area, sf::Color Color, sf::Vector2f position, int numOfPeoples);
    ~ClCrowd();

    void Update(sf::Vector2i position,float frameTime);
    void Update(float frameTime);
    void Draw(sf::RenderWindow& window);

    const sf::Vector2f  getMassPoint();
    float getRadius();

    const std::vector<StrPeople *> & getPeoples() {return peoples;}
private:
    /// ToDo : Add computer independent force toggeling
    int toggleForce; // used to calculate different forces each time ClCrowd is called

    void Vec2DNormalize( sf::Vector2f *NormalizeMe );
    sf::Vector2f Seek(sf::Vector2f TargetPos, const sf::Vector2f & Destination, const sf::Vector2f & CurVelocity);
    float invert(float Max, float Current);
    sf::Vector2f DistanceForce(int current);
    //sf::Vector2f Cohesion(StrPeople* start, const sf::Vector2f & massPoint, int current);

    ClArea *Area; // used for collision detection
    std::vector<StrPeople *> peoples;
    sf::Vector2f position;
    float radius;

    // for debugging puposes : each Crowd does have a unique color

    sf::Color Color;


};

#endif // CROWD2_HPP_INCLUDED
