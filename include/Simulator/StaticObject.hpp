#include <SFML/Graphics.hpp>
#ifndef C_STATIC_OBJECT_INCLUDE
#define C_STATIC_OBJECT_INCLUDE

#include <iostream>
#include <math.h>

class ClStaticObject
{
public:
    ClStaticObject(sf::RectangleShape *Rectconst);
    ~ClStaticObject();
    void draw(sf::RenderWindow& window);
    void update(  );
    bool isInRange( const sf::Vector2f & massPoint, float radius);
    //if a circle meets a rectangle
    float intersection_circle(const sf::Vector2f & massPoint, float radius);
    void highlightRect() /// delete this function
    {
        highlight = true;
    }
    bool Intersects( const sf::Vector2f  &Position)
    {
        return Rect->getGlobalBounds().contains(Position);
    }
private:

    void updateCenter();
    const sf::Vector3f calculateLineFunc(const sf::Vector2f & p1, const sf::Vector2f & p2);
    const sf::Vector3f solveQuadrEquation(const sf::Vector3f & incoming);
    void calculateIntersectionPoints( const sf::Vector3f & Outline, const sf::Vector2f & massPoint, float radius );

    sf::RectangleShape *Rect;
    sf::Vector2f Center;
    int id;
    float rectRadius;
    sf::Vector2f helpVec[8]; // represents the 8 possible intersection points
    bool highlight;
};

#endif // C_STATIC_OBJECT_INCLUDE
