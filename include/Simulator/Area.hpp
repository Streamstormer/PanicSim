#ifndef AREA_HPP_INCLUDED
#define AREA_HPP_INCLUDED

#include "StaticObject.hpp"
#include <vector>

enum staticObjects{Stage, Bar, WC, Wall, Fence };

class ClArea
{
    public:
    ClArea() {}
    ~ClArea();

    void insertStObj(enum staticObjects, const sf::Vector2f & sizeOfRectangle,const sf::Vector2f & positionOfRectangle);
    void draw(sf::RenderWindow& window);
    bool validPoint(sf::Vector2f point);

    private:
    std::vector<ClStaticObject *> sobjects;
};

#endif // AREA_HPP_INCLUDED
