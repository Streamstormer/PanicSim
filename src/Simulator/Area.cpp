#include "../../include/Simulator/Area.hpp"
    ClArea::~ClArea()
    {
        for(unsigned int n=0; n < sobjects.size(); n++)
        {
            delete sobjects[n];
        }
    }

    int ClArea::insertStObj(enum staticObjects type, const sf::Vector2f & sizeOfRectangle,
                            const sf::Vector2f & positionOfRectangle, float rotAngle)
    {
        id++;
        sf::RectangleShape *tempRe = new sf::RectangleShape();
        tempRe->setPosition(positionOfRectangle);
        tempRe->setSize(sizeOfRectangle);
        tempRe->setRotation(rotAngle);
        ClStaticObject *tempSt = new ClStaticObject(tempRe, id, (int) type);
        sobjects.push_back(tempSt);
        return id;
    }


    void ClArea::draw(sf::RenderWindow& window)
    {
        for(unsigned int n=0; n < sobjects.size(); n++)
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

/// Get Methods for static Object attributes via the id
/// for the editor

    const sf::Vector2f & ClArea::getPosition(int id)
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                return sobjects[n]->getPosition();
            }
        }
    }
    const sf::Vector2f & ClArea::getSize(int id)
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                return sobjects[n]->getSize();
            }
        }
    }
    float ClArea::getRotation(int id)
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                return sobjects[n]->getRotation();
            }
        }
    }

    int ClArea::getType(int id)
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                return sobjects[n]->getType();
            }
        }
    }


    /// Set Methods for StaticObjects attributes via id and new value
    /// for the editor

    void ClArea::setPosition(int id, const sf::Vector2f &position) // sets position of StaticObject via id
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                sobjects[n]->setPosition(position);
            }
        }
    }
    void ClArea::setSize(int id, const sf::Vector2f &newSize)         // sets size of StaticObject via id
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                sobjects[n]->setSize(newSize);
            }
        }
    }
    void ClArea::setRotation(int id, float rotation)               // sets rotation of StaticObject via id
    {
        for (unsigned int n = 0; n < sobjects.size();n++)
        {
            if (sobjects[n]->getID() == id)
            {
                sobjects[n]->setRotation(rotation);
            }
        }
    }
