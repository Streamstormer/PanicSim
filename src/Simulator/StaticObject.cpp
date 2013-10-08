#include "../../include/Simulator/StaticObject.hpp"

ClStaticObject::ClStaticObject(sf::RectangleShape *Rectconst, int id)
{
    sf::Vector2f RectSize = Rectconst->getSize();
    Rect = Rectconst;

    this->id = id;
}

ClStaticObject::~ClStaticObject()
{
    delete Rect;
}

void ClStaticObject::draw(sf::RenderWindow& window)
{
    window.draw(*Rect);
}
bool ClStaticObject::Intersects( const sf::Vector2f  &Position)
    {
        return Rect->getGlobalBounds().contains(Position);
    }
    int ClStaticObject::getID()
    {
        return id;
    }
    const sf::Vector2f &ClStaticObject::getPosition()
    {
        return Rect->getPosition();
    }
    const sf::Vector2f &ClStaticObject::getSize()
    {
        return Rect->getSize();
    }

    float ClStaticObject::getRotation()
    {
        return Rect->getRotation();
    }

    void ClStaticObject::setPosition(const sf::Vector2f &position)
    {
        Rect->setPosition(position);
    }
    void ClStaticObject::setRotation(float rotation)
    {
        Rect->setRotation(rotation);
    }
    void ClStaticObject::setSize(const sf::Vector2f &newSize)
    {
        Rect->setSize(newSize);
    }
