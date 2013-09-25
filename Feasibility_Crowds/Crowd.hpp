#ifndef CROWD_HPP_INCLUDED
#define CROWD_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class c_crowd
{
public:
    c_crowd(float radius);
    ~c_crowd();

    void update(sf::Vector2i Position);
    void draw(sf::RenderWindow& window);

    const sf::Vector2f getMasspoint();

    float getRadius() {return radius;}
private:
    sf::Vector2f Position;
    float radius;
    sf::CircleShape Circle;
};

#endif // CROWD_HPP_INCLUDED
