#include <iostream>
#include "Crowd.hpp"
#include "Area.hpp"
#include "Crowd_2.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 640), "Panic Sim!");
    sf::Vector2f Position;
    Position.x = 1000.0f;
    Position.y = 1000.0f;

    ClArea Area;
    Area.insertStObj(sf::Vector2f(50,100), sf::Vector2f(250,120));
    Area.insertStObj(sf::Vector2f(120,350), sf::Vector2f(500,200));
    Area.insertStObj(sf::Vector2f(150,80), sf::Vector2f(40,400));

    //c_crowd Crowd(50);
    ClCrowd Crowd2(50, &Area);


    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();

        /// Update
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Crowd2.update(sf::Mouse::getPosition(), elapsed.asMilliseconds());


        ///Render
        window.clear();
        Crowd2.draw(window);
        Area.draw(window);
        window.display();
    }
    return 0;
}
