#include <iostream>
#include "Crowd.hpp"
#include "Area.hpp"
#include "CrowdManager.hpp"

int main()
{
  //  sf::VideoMode Mode = sf::VideoMode::getFullscreenModes();
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Panic Sim!");
    sf::Vector2f Position;
    Position.x = 1000.0f;
    Position.y = 1000.0f;

    ClArea Area;
    Area.insertStObj(sf::Vector2f(50,100), sf::Vector2f(250,120));
    Area.insertStObj(sf::Vector2f(120,350), sf::Vector2f(500,200));
    Area.insertStObj(sf::Vector2f(150,80), sf::Vector2f(40,400));

    ClCrowdManager CrowdManager(&Area);
    CrowdManager.CreateCrowd(sf::Vector2f(300,250),150,100);
    CrowdManager.CreateCrowd(sf::Vector2f(550,350),150,200);
    CrowdManager.CreateCrowd(sf::Vector2f(250,523),150,1500);

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

        CrowdManager.Update(elapsed.asMilliseconds());


        ///Render
        window.clear();
        CrowdManager.Draw(window);
        Area.draw(window);
        window.display();
    }
    return 0;
}
