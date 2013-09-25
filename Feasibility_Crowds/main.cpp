#include <iostream>
#include "static_object.hpp"
#include "Crowd.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 640), "SFML works!");
    sf::Vector2f Position;
    Position.x = 1000.0f;
    Position.y = 1000.0f;
    sf::RectangleShape Rect(Position);

    c_crowd Crowd(50);

    Rect.setPosition(Position);

    c_static_object stObj(Rect, Position);

    stObj.isInRange(sf::Vector2f (0,0),0.f);

    while (window.isOpen())
    {
        /// Update
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Crowd.update(sf::Mouse::getPosition());
        if(stObj.isInRange(Crowd.getMasspoint(),Crowd.getRadius()))
        {
            stObj.intersection_circle(Crowd.getMasspoint(),Crowd.getRadius());
            stObj.update(true);
        }
        else
        {

            stObj.update(false);
        }

        ///Render
        window.clear();
        Crowd.draw(window);
        stObj.draw(window);
        window.display();
    }
    return 0;
}
