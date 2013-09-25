#ifndef CROWD_HPP_INCLUDED
#define CROWD_HPP_INCLUDED

class c_crowd
{
public:
    c_crowd(float radius)
    {
        this->radius = radius;
        Circle.setRadius(radius);
        Circle.setFillColor(sf::Color::Blue);
    }

    ~c_crowd() {}

    void update(sf::Vector2i Position)
    {
        /// Provisorium
        this->Position.x = (float)Position.x;
        this->Position.y = (float)Position.y;
        Circle.setPosition(this->Position);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(Circle);
    }

    const sf::Vector2f getMasspoint()
    {
        sf::Vector2f masspoint(Position);
        masspoint.x += radius;
        masspoint.y += radius;
        return masspoint;
    }
    float getRadius() {return radius;}
private:
    sf::Vector2f Position;
    float radius;
    sf::CircleShape Circle;
};

#endif // CROWD_HPP_INCLUDED
