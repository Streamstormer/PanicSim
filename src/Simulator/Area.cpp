#include "../../include/Simulator/Area.hpp"
    ClArea::~ClArea()
    {
        for(int n=0; n < sobjects.size(); n++)
        {
            delete sobjects[n];

        }
    }

    void ClArea::insertStObj(enum staticObjects, const sf::Vector2f & sizeOfRectangle,const sf::Vector2f & positionOfRectangle)
    {
        sf::RectangleShape *tempRe = new sf::RectangleShape();
        tempRe->setPosition(positionOfRectangle);
        tempRe->setSize(sizeOfRectangle);
        ClStaticObject *tempSt = new ClStaticObject(tempRe);
        sobjects.push_back(tempSt);
    }


    void ClArea::draw(sf::RenderWindow& window)
    {
        for(int n=0; n < sobjects.size(); n++)
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

