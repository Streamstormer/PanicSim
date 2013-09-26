#include <iostream>
#include "Crowd.hpp"
#include "Area.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 640), "SFML works!");
    sf::Vector2f Position;
    Position.x = 1000.0f;
    Position.y = 1000.0f;

    c_crowd Crowd(50);

    C_Area Area;
    Area.insertStObj(sf::Vector2f(50,100), sf::Vector2f(250,120));
    Area.insertStObj(sf::Vector2f(120,350), sf::Vector2f(500,200));
    Area.insertStObj(sf::Vector2f(150,80), sf::Vector2f(40,400));



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

        Area.checkIntersection(Crowd.getMasspoint(),Crowd.getRadius());
        Area.update();

        ///Render
        window.clear();
        Crowd.draw(window);
        Area.draw(window);
        window.display();
    }
    return 0;
}
