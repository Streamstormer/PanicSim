#include "../../include/Simulator/Area.hpp"
    ClArea::~ClArea()
    {
    }

    void ClArea::insertStObj(const sf::Vector2f & sizeOfRectangle,const sf::Vector2f & positionOfRectangle)
    {
        sf::RectangleShape tempRe;
        tempRe.setPosition(positionOfRectangle);
        tempRe.setSize(sizeOfRectangle);
        ClStaticObject *tempSt = new ClStaticObject(tempRe,positionOfRectangle);
        sobjects.push_back(tempSt);
    }


    void ClArea::draw(sf::RenderWindow& window)
    {
        signed int n;
        for( n=0; n < sobjects.size(); n++)
        {
            sobjects[n]->draw(window);

        }


    }
    bool ClArea::validPoint(sf::Vector2f point)
    {
        for( unsigned int n=0; n < sobjects.size(); n++)
        {
            if(sobjects[n]->Intersects(point))
            {
                return false;
            }
        }
         return true;
    }

