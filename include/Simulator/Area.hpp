#ifndef AREA_HPP_INCLUDED
#define AREA_HPP_INCLUDED

#include "StaticObject.hpp"
#include <vector>


class ClArea
{
    public:

    ClArea() {id = 0;}
    ~ClArea();

    int insertStObj(enum staticObjects type, const sf::Vector2f & sizeOfRectangle,
                    const sf::Vector2f & positionOfRectangle, float rotAngle);
    void draw(sf::RenderWindow& window);
    bool validPoint(sf::Vector2f point); // returns whether a point is inside a staticObject ( false ) or not ( true )
    int  getIdByVector(sf::Vector2f mouse); // returns -1 when mouse is not inside any staticObject

    /// Get and Set for StaticObjects

    /// Get Methods for StaticObjects attributes via the id
    /// for the editor

    const sf::Vector2f & getPosition(int id);   // returns position of a StaticObject via id
    const sf::Vector2f & getSize(int id);       // returns size of a StaticObject via id
    float getRotation(int id);                  // returns rotation of a StaticObject via id

    /// not for the editor but for the collision detection / for the pathFinder

    const sf::Vector2f & getSource(int id);
    const sf::Vector2f getClosestExit(const sf::Vector2f & myPosition)
    {
        float distance = INFINITY;
        sf::Vector2f closestExitPosition;
        for(unsigned int n = 0; n < sobjects.size(); n++)
        {
            if (sobjects[n]->getType() == GATE)
            {
                sf::Vector2f position = sobjects[n]->getCenter();
                float testDistance = (myPosition.x - position.x)*(myPosition.x - position.x)+(myPosition.y - position.y)*(myPosition.x - position.x);
                if (testDistance<distance)
                {
                    closestExitPosition = position;
                    distance = testDistance;
                }

            }
        }
        return closestExitPosition;
    }

    /// Set Methods for StaticObjects attributes via id and new value
    /// for the editor

    void setPosition(int id, const sf::Vector2f &position);     // sets position of StaticObject via id
    void setSize(int id, const sf::Vector2f &newSize);          // sets size of StaticObject via id
    void setRotation(int id, float rotation);                   // sets rotation of StaticObject via id

    /// For the FileHandler
    int getNumberOfStaticObjects() {return id;}     // return total number of static objects
                                                    // ids of static objects start at id = 1 !!!
    enum staticObjects getType(int id);                            // returns Type of a StaticObject via id

    void setLevelSize(sf::Vector2i pLevelSize){levelSize.x = pLevelSize.x; levelSize.y = pLevelSize.y;};
    void setBgColor(sf::Color pColor){bgColor.r = pColor.r; bgColor.g = pColor.g; bgColor.b = pColor.b;};
    sf::Color getBgColor(){return bgColor;};
    sf::Vector2i getLevelSize(){return levelSize;};

    bool validPath(sf::Vector2f startPoint, sf::Vector2f endPoint); //returns ture if the neighbour is valid

    private:

    int id; // used to give StaticObjects a unique id
    std::vector<ClStaticObject *> sobjects;
    sf::Vector2i levelSize;
    sf::Color bgColor;
};

#endif // AREA_HPP_INCLUDED
