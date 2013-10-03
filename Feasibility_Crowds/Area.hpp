#ifndef AREA_HPP_INCLUDED
#define AREA_HPP_INCLUDED

#include "static_object.hpp"
#include <vector>

class ClArea
{
    public:
    ClArea() {}
    ~ClArea()
    {


        std::cout << "size :" << sobjects.size() << std::endl;
    }

    void insertStObj(const sf::Vector2f & sizeOfRectangle,const sf::Vector2f & positionOfRectangle)
    {
        sf::RectangleShape tempRe;
        tempRe.setPosition(positionOfRectangle);
        tempRe.setSize(sizeOfRectangle);
        c_static_object tempSt(tempRe,positionOfRectangle);
        sobjects.push_back(tempSt);
    }

    void update()
    {
    //    std::vector<c_static_object *>::const_iterator cii;
        for(cii=sobjects.begin(); cii!=sobjects.end(); cii++)
        {
//            (*cii).update();
        }
    }

    float checkIntersection( const sf::Vector2f & massPoint, float radius) // returns the size of the Areas that intersects with the circle
    {
     /*   float totalArea = 0;
      //  std::vector<c_static_object *>::const_iterator cii;
        for(cii=sobjects.begin(); cii!=sobjects.end(); cii++)
        {
            if ((*cii).(massPoint,radius) == true)
            {
                totalArea += (*cii)->intersection_circle(massPoint,radius);
            }
        }
        return totalArea; */ return -1;
    }

    void draw(sf::RenderWindow& window)
    {
        signed int n;
    //    std::vector<c_static_object *>::const_iterator cii;
        for( n=0; n < sobjects.size(); n++)
        {
            sobjects[n].draw(window);

        }


    }
    bool ValidPoint(sf::Vector2f point)
    {
        for( unsigned int n=0; n < sobjects.size(); n++)
        {
            if(sobjects[n].Intersects(point))
            {
                return false;
            }
        }
         return true;
    }
    private:
    std::vector<c_static_object> sobjects;
    std::vector<c_static_object>::const_iterator cii;
};

#endif // AREA_HPP_INCLUDED
