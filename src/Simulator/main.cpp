#include <iostream>
#include <string>
#include <getopt.h>

#include "../../include/Simulator/Simulation.hpp"

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
    sf::VideoMode Mode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(Mode, "Panic Sim!");
    ClSimulation *pSimulation = new ClSimulation(Mode);

    while (window.isOpen())
    {
        /// Update
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        pSimulation->update(window);

        ///Render
        window.clear();
        pSimulation->draw(window);
        window.display();
    }
    return 0;
}
