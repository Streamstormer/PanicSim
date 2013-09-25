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
        //   This tests the calculateLineFunc function
        //   sf::Vector2f Hallo = calculateLineFunc(sf::Vector2f(2,2),sf::Vector2f(3,1));
        //   std::cout << "m :" << Hallo.x << "c :" << Hallo.y << std::endl;
        sf::Vector3f Quadr(2,1,1);
        Quadr = this->solveQuadrEquation(Quadr);
        std::cout << "x: " << Quadr.x << "x2 : " << Quadr.y << "num of sol :" << Quadr.z << std::endl;
    }
    void draw(sf::RenderWindow& window)
    {
        sf::CircleShape Shape(1);
        Shape.setFillColor(sf::Color::White);
        Shape.setPosition(Center);
        window.draw(Rect);
        window.draw(Shape);
        Shape.setFillColor(sf::Color::Yellow);
        for(int n=0;n<2;n++)
        {

            if(helpVec[n].x != -1)
            {
                Shape.setPosition(helpVec[n]);
                window.draw(Shape);
            }
        }
    }
    void update( bool rotation )
    {
        Rect.setFillColor(sf::Color::Red);
        if (rotation)
        {
            Rect.setFillColor(sf::Color::Green);
        }
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

        sf::Vector2f Outline(this->calculateLineFunc(topLeft,topRight));
        sf::Vector3f intersEq(Outline.x * Outline.x + 1, -2*massPoint.x+2*Outline.x*(Outline.y-massPoint.y),(Outline.y-massPoint.y)*(Outline.y-massPoint.y) -(radius * radius) + (massPoint.x*massPoint.x));
        intersEq = this->solveQuadrEquation(intersEq);
        helpVec[0].x = helpVec[1].x = -1;
        if ( intersEq.z > 0)
        {
            helpVec[0].x = intersEq.x;
            helpVec[0].y = intersEq.x * Outline.x + Outline.y;
            if ( intersEq.z > 1)
            {
                helpVec[1].x = intersEq.y;
                helpVec[1].y = intersEq.y * Outline.x + Outline.y;
            }
        }


        /*
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
        */

    return -1;

    }

private:
    void updateCenter()
    {
        Center = Rect.getPosition();
        sf::Vector2f Size = Rect.getSize();
        Center.x += Size.x / 2;
        Center.y += Size.y / 2;
    }

    const sf::Vector2f calculateLineFunc(const sf::Vector2f & p1, const sf::Vector2f & p2)
    {
        // gives back a line function of the form y = mx+c
        // m = LineFunc.x
        // c = LineFunc.y

        sf::Vector2f LineFunc; // represents function
        // Calculate m

        if (p1.x != p2.x)
        {
            LineFunc.x = (p1.y-p2.y) / (p1.x-p2.x);
        }
        else
        {
            LineFunc.x = 0;
        }
        //Calculate c
        LineFunc.y = -1* LineFunc.x * p1.x + p1.y;
        return LineFunc;
    }
    const sf::Vector3f solveQuadrEquation(const sf::Vector3f & incoming)
    {
        // A x^2 + B x + c = 0
        // A > 0

        // incoming.x = A
        // incoming.y = B
        // incoming.z = C
        // solution.x = solution1
        // solution.y = solution2
        // solution.z = number of solutions

        float p= incoming.y/(2*incoming.x);
        float d=p*p - incoming.z/incoming.x;
        sf::Vector3f solution;
        if (d<0) // no solutions given
        {
            solution.z = 0;
        }
        else
        {
            if (d==0) // one solution
            {
                solution.x=-p;
                solution.z=1;
            }
            else // two solutions
            {
                solution.x=-p + sqrt(d);
                solution.y=-p - sqrt(d);
                solution.z = 2;
            }
        }
        return solution;
    }
    sf::RectangleShape Rect;
    sf::Vector2f Center;
    int id;
    float rectRadius;
    sf::Vector2f helpVec[8]; // represents the 8 possible intersection points
};

#endif // C_STATIC_OBJECT_INCLUDE
