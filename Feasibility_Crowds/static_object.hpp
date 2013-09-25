#include <SFML/Graphics.hpp>
#ifndef C_STATIC_OBJECT_INCLUDE
#define C_STATIC_OBJECT_INCLUDE

#include <iostream>
#include <math.h>

class c_static_object
{
public:
    c_static_object(const sf::RectangleShape& Rectconst, sf::Vector2<float>& Position);
    void draw(sf::RenderWindow& window);
    void update( bool rotation );
    bool isInRange( const sf::Vector2f & massPoint, float radius);
    //if a circle meets a rectangle
    float intersection_circle(const sf::Vector2f & massPoint, float radius);

private:

    void updateCenter();
    const sf::Vector3f calculateLineFunc(const sf::Vector2f & p1, const sf::Vector2f & p2);
    const sf::Vector3f solveQuadrEquation(const sf::Vector3f & incoming);
    void calculateIntersectionPoints( const sf::Vector3f & Outline, const sf::Vector2f & massPoint, float radius );


        sf::RectangleShape Rect;
        sf::Vector2f Center;
        int id;
    float rectRadius;
    sf::Vector2f helpVec[8]; // represents the 8 possible intersection points
};

#endif // C_STATIC_OBJECT_INCLUDE
