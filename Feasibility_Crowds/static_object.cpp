#include "static_object.hpp"
c_static_object::c_static_object(const sf::RectangleShape& Rectconst, sf::Vector2<float>& Position)
{
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(100, 100));
    rectangle.setPosition(500, 500);
    Rect = rectangle;
    rectRadius = 50;
    updateCenter();

}
void c_static_object::draw(sf::RenderWindow& window)
{
    sf::CircleShape Shape(1);
    Shape.setFillColor(sf::Color::White);
    Shape.setPosition(Center);
    window.draw(Rect);
    window.draw(Shape);
    Shape.setFillColor(sf::Color::Red);
    for(int n=0; n<8; n++)
    {

        if(helpVec[n].x != -1)
        {
            Shape.setPosition(helpVec[n]);
            window.draw(Shape);
        }
    }
}
void c_static_object::update( bool rotation )
{
    Rect.setFillColor(sf::Color::Red);
    if (rotation)
    {
        Rect.setFillColor(sf::Color::Green);
    }
}

bool c_static_object::isInRange( const sf::Vector2f & massPoint, float radius)
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
float c_static_object::intersection_circle(const sf::Vector2f & massPoint, float radius)
{
    //calculate function to localize the edges of a static object
    //calculate intersection points
    //calculate intersection area

    for (int n=0; n<8; n++)
    {
        helpVec[n].x = -1;
    }

    //1.

    sf::FloatRect borders = Rect.getGlobalBounds();
    sf::Vector2f topLeft (borders.top, borders.left);
    sf::Vector2f topRight (borders.top + borders.width,  borders.left );
    sf::Vector2f downLeft (borders.top, borders.left + borders.height);
    sf::Vector2f downRight (borders.top + borders.width, borders.left + borders.height);

    //2. + 3.

    // top line intersection points
    sf::Vector3f Outline(this->calculateLineFunc(topLeft,topRight));
    calculateIntersectionPoints( Outline, massPoint, radius );

    // bottom line intersection points
    Outline = this->calculateLineFunc(downLeft,downRight);
    calculateIntersectionPoints( Outline, massPoint, radius );

    // left line intersection points

    Outline = this->calculateLineFunc(topLeft,downLeft);
    calculateIntersectionPoints( Outline, massPoint, radius );

    // right line intersection points
    Outline = (this->calculateLineFunc(downRight,topRight));
    calculateIntersectionPoints( Outline, massPoint, radius );

    return -1;

}

void c_static_object::updateCenter()
{
    Center = Rect.getPosition();
    sf::Vector2f Size = Rect.getSize();
    Center.x += Size.x / 2;
    Center.y += Size.y / 2;
}

const sf::Vector3f c_static_object::calculateLineFunc(const sf::Vector2f & p1, const sf::Vector2f & p2)
{
    // gives back a line function of the form y = mx+c
    // m = LineFunc.x
    // c = LineFunc.y

    sf::Vector3f LineFunc; // represents function

    // Special cases
    if (p1.y == p2.y)
    {
        LineFunc.x = 0;
        LineFunc.y = p1.y;
        LineFunc.z = -1;
        return LineFunc;
    }
    else if (p1.x == p2.x)
    {
        LineFunc.x = LineFunc.y = 0;
        LineFunc.z = p1.x;
        return LineFunc;
    }
    // Calculate m
    LineFunc.x = (p1.y-p2.y) / (p1.x-p2.x);
    //Calculate c
    LineFunc.y = -1* LineFunc.x * p1.x + p1.y;
    LineFunc.z = -1;
    return LineFunc;
}
const sf::Vector3f c_static_object::solveQuadrEquation(const sf::Vector3f & incoming)
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

void c_static_object::calculateIntersectionPoints( const sf::Vector3f & Outline, const sf::Vector2f & massPoint, float radius )
{
        sf::Vector3f intersEq;
        int n = 0;

        while(helpVec[n].x != -1 && n < 8)
        {
            n++;
        }

        if (Outline.z != -1)
        {
            float savex = Outline.z;
            intersEq.x = 1;
            intersEq.y = -2*massPoint.y;
            intersEq.z = Outline.z * Outline.z - 2 * Outline.z * massPoint.x + massPoint.x * massPoint.x + massPoint.y * massPoint.y - radius * radius;
            intersEq = this->solveQuadrEquation(intersEq);

            if ( intersEq.z > 0)
            {
                helpVec[n].x = savex;
                helpVec[n].y = intersEq.x;

                if ( intersEq.z > 1)
                {
                    helpVec[n+1].y = intersEq.y;
                    helpVec[n+1].x = savex;
                }
            }
        }
        else
        {
            intersEq.x =(Outline.x * Outline.x) + 1;
            intersEq.y = -2*massPoint.x+2*Outline.x*(Outline.y-massPoint.y);
            intersEq.z =(Outline.y-massPoint.y)*(Outline.y-massPoint.y) -(radius * radius) + (massPoint.x*massPoint.x);
            intersEq = this->solveQuadrEquation(intersEq);

            if ( intersEq.z > 0)
            {
                helpVec[n].x = intersEq.x;
                helpVec[n].y = intersEq.x * Outline.x + Outline.y;
                if ( intersEq.z > 1)
                {
                    helpVec[n+1].x = intersEq.y;
                    helpVec[n+1].y = intersEq.y * Outline.x + Outline.y;
                }
            }
        }
}
