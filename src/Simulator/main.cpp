#include <iostream>
#include <string>
#include <getopt.h>
#include "../../include/Simulator/Crowd.hpp"
#include "../../include/Simulator/Area.hpp"
#include "../../include/Simulator/CrowdManager.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    int opts;
    while((opts = getopt(argc, argv, "f:")) != -1){
        switch(opts){
            case 'f': {
                string filePath(optarg);
                break;
            }
            default: {
                cerr<<"Wrong option: "<<opts<<endl;
                return EXIT_FAILURE;
            }
        }
    }

  //  sf::VideoMode Mode = sf::VideoMode::getFullscreenModes();
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Panic Sim!");
    sf::Vector2f Position;
    Position.x = 1000.0f;
    Position.y = 1000.0f;

    ClArea Area;
    Area.insertStObj(Stage, sf::Vector2f(50,100), sf::Vector2f(250,120));
    Area.insertStObj(Bar, sf::Vector2f(120,350), sf::Vector2f(500,200));
    Area.insertStObj(WC, sf::Vector2f(150,80), sf::Vector2f(40,400));

    ClCrowdManager CrowdManager(&Area);
    CrowdManager.CreateCrowd(sf::Vector2f(300,250),150,100);
    CrowdManager.CreateCrowd(sf::Vector2f(550,350),150,200);
    CrowdManager.CreateCrowd(sf::Vector2f(250,523),150,150);

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
        sf::Vector2f temp = Area.getPosition(1);
        temp.x += 0.01;
        Area.setPosition(1,temp);

        ///Render
        window.clear();
        CrowdManager.Draw(window);
        Area.draw(window);
        window.display();
    }
    return 0;
}
