#ifndef AREA_HPP_INCLUDED
#define AREA_HPP_INCLUDED

#include "static_object.hpp"
#include <vector>

class C_Area
{
    public:
    C_Area() {}
    ~C_Area()
    {
        std::vector<c_static_object *>::const_iterator cii;
        for(cii=sobjects.begin(); cii!=sobjects.end(); cii++)
        {
            delete (*cii);
        }


        std::cout << "size :" << sobjects.size() << std::endl;
    }

    void insertStObj(const sf::Vector2f & sizeOfRectangle,const sf::Vector2f & positionOfRectangle)
    {
        sf::RectangleShape tempRe;
        tempRe.setPosition(positionOfRectangle);
        tempRe.setSize(sizeOfRectangle);
        c_static_object *tempSt = new c_static_object(tempRe,positionOfRectangle);
        sobjects.push_back(tempSt);
    }

    void update()
    {
        std::vector<c_static_object *>::const_iterator cii;
        for(cii=sobjects.begin(); cii!=sobjects.end(); cii++)
        {
            (*cii)->update();
        }
    }

    float checkIntersection( const sf::Vector2f & massPoint, float radius) // returns the size of the Areas that intersects with the circle
    {
        float totalArea = 0;
        std::vector<c_static_object *>::const_iterator cii;
        for(cii=sobjects.begin(); cii!=sobjects.end(); cii++)
        {
            if ((*cii)->isInRange(massPoint,radius) == true)
            {
                totalArea += (*cii)->intersection_circle(massPoint,radius);
            }
        }
        return totalArea;
    }

    void draw(sf::RenderWindow& window)
    {
        std::vector<c_static_object *>::const_iterator cii;
        for(cii=sobjects.begin(); cii!=sobjects.end(); cii++)
        {
            (*cii)->draw(window);
        }
    }
    private:
    std::vector<c_static_object *> sobjects;
};

#endif // AREA_HPP_INCLUDED
