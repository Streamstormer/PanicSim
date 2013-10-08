#ifndef AREA_HPP_INCLUDED
#define AREA_HPP_INCLUDED

#include "StaticObject.hpp"
#include <vector>

enum staticObjects{Stage, Bar, WC, Wall, Fence };

class ClArea
{
    public:

    ClArea() {id = 0;}
    ~ClArea();

    int insertStObj(enum staticObjects, const sf::Vector2f & sizeOfRectangle,const sf::Vector2f & positionOfRectangle);
    void draw(sf::RenderWindow& window);
    bool validPoint(sf::Vector2f point);

    /// Get and Set for StaticObjects

    /// Get Methods for StaticObjects attributes via the id
    /// for the editor

    const sf::Vector2f & getPosition(int id);   // returns position of StaticObject via id
    const sf::Vector2f & getSize(int id);       // returns size of StaticObject via id
    const float getRotation(int id);            // returns rotation of StaticObject via id

    /// Set Methods for StaticObjects attributes via id and new value
    /// for the editor

    void setPosition(int id, const sf::Vector2f &position);     // sets position of StaticObject via id
    void setSize(int id, const sf::Vector2f &newSize);          // sets size of StaticObject via id
    void setRotation(int id, float rotation);                   // sets rotation of StaticObject via id

    private:

    int id; // used to give StaticObjects a unique id
    std::vector<ClStaticObject *> sobjects;
};

#endif // AREA_HPP_INCLUDED
