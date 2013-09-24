#include <SFML/Graphics.hpp>
#ifndef C_STATIC_OBJECT_INCLUDE
#define C_STATIC_OBJECT_INCLUDE

#include <iostream>
#include <math.h>

class c_static_object
{
public:
    c_static_object(const sf::RectangleShape& Rectconst, sf::Vector2<float>& Position)
    {
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(100, 100));
        rectangle.setPosition(100, 100);
        Rect = rectangle;
        rectRadius = 50;
        updateCenter();

    }
    void draw(sf::RenderWindow& window)
    {
        sf::CircleShape Shape(1);
        Shape.setFillColor(sf::Color::Red);
        Shape.setPosition(Center);
        window.draw(Rect);
        window.draw(Shape);
    }
    void update( bool rotation )
    {
        Rect.setFillColor(sf::Color::Red);
        if (rotation)
        {
            Rect.setFillColor(sf::Color::Green);
        }
    }
    float Intersects( const sf::Vector2f & massPoint, float radius)
    {

    }
    bool isInRange( const sf::Vector2f & massPoint, float radius)
    {
        sf::Vector2f delta(massPoint);
        int a = abs(massPoint.x-Center.x);
        int b = abs(massPoint.y-Center.y);
        int c = (int)sqrt((a*a)+(b*b));

        int c_rec = (int)sqrt((5000));

        if(c<(c_rec+radius))
        {
            return true;
        }
        return false;
/*
        delta.x -= Center.x;
        delta.y -= Center.y;

        delta.x *= delta.x;
        delta.y *= delta.y;

        if ((delta.x + delta.y) <= (rectRadius*rectRadius)+(radius*radius))
        {
            return true;
        }
        return false;
*/
    }
//if a circle meets a rectangle
    float intersection_circle(const sf::Vector2f & massPoint, float radius)
    {
        //calculate function to localize the edges of a static object
        //calculate intersection points
        //calculate intersection area

        //1.

        sf::FloatRect borders = Rect.getGlobalBounds();
        sf::Vector2f topLeft (borders.top, borders.left);
        sf::Vector2f topRight (borders.top,  borders.left + borders.width);
        sf::Vector2f downLeft (borders.top + borders.height, borders.left);
        sf::Vector2f downRight (borders.top + borders.height, borders.left + borders.width);

        //Objects can not be rotated!
        //Borders are described with just a single value horizontal or vertical
        float border_x_function_top = borders.top;
        float border_x_function_down = (borders.top + borders.height);

        float border_y_function_left = borders.left;
        float border_y_function_right = (borders.left + borders.width);

        sf::Vector2f intersectionPoint1 (borders.top , -1);
        //check if the intersectionPoints are on the Borders
        //    intersectionPoint1_x_function_top.y = (sqrt(radius*radius - (abs(intersectionPoint1.x - massPoint.x) * (abs(intersectionPoint1.x - massPoint.x)))) - massPoint.y)) ;
        //    intersectionPoint2_x_function_top.y = (sqrt(radius*radius - (abs(intersectionPoint1.x - massPoint.x) * (abs(intersectionPoint1.x - massPoint.x)))) + massPoint.y) ;
    }
private:
    void updateCenter()
    {
        Center = Rect.getPosition();
        sf::Vector2f Size = Rect.getSize();
        Center.x += Size.x / 2;
        Center.y += Size.y / 2;
    }
    sf::RectangleShape Rect;
    sf::Vector2f Center;
    int id;
    float rectRadius;
};

#endif // C_STATIC_OBJECT_INCLUDE
