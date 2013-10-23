#include <iostream>
#include <string>
#include <getopt.h>

#include "../../include/Simulator/Simulation.hpp"
#include "../../include/Simulator/SimpleGUI.hpp"

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
    ClSimpleGUI *pGUI = new ClSimpleGUI(sf::Vector2f(Mode.width,Mode.height));
    bool mouseReleased = false;
    while (window.isOpen())
    {
        /// Update
        sf::Event event;
        mouseReleased = false;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();

            if(event.type == sf::Event::MouseButtonReleased )
            {
                mouseReleased = true;
            }
        }


        // Update Simulation
        pSimulation->update(window, mouseReleased);
        // Update GUI
        pGUI->update(window, mouseReleased);
        ///Render
        window.clear();
        pSimulation->draw(window);
        // Draw GUI
        // reset View so GUI is drawn at the same position everytime
        window.setView(window.getDefaultView());
        pGUI->draw(window);
        window.display();
    }
    delete pSimulation;
    delete pGUI;
    return 0;
}
