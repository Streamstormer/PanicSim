#include "Crowd.hpp"

    c_crowd::c_crowd(float radius)
    {
        this->radius = radius;
        Circle.setRadius(radius);
        Circle.setFillColor(sf::Color::Blue);
    }

    c_crowd::~c_crowd() {}

    void c_crowd::update(sf::Vector2i Position)
    {
        /// Provisorium
        this->Position.x = (float)Position.x;
        this->Position.y = (float)Position.y;
        Circle.setPosition(this->Position);
    }

    void c_crowd::draw(sf::RenderWindow& window)
    {
        window.draw(Circle);
    }

    const sf::Vector2f c_crowd::getMasspoint()
    {
        sf::Vector2f masspoint(Position);
        masspoint.x += radius;
        masspoint.y += radius;
        return masspoint;
    }
