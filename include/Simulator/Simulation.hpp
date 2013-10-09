#ifndef SIMULATION_HPP_INCLUDED
#define SIMULATION_HPP_INCLUDED

#include "../../include/Simulator/Crowd.hpp"
#include "../../include/Simulator/Area.hpp"
#include "../../include/Simulator/CrowdManager.hpp"
#include "../../include/Simulator/SimpleGUI.hpp"

class ClSimulation
{
    public:

        ClSimulation(const sf::VideoMode &Mode);
        ~ClSimulation();
        bool update(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

    private:

        void CreateObjects(); // FileHandler logic goes here
                              // this function is called in the constructor

        ClArea *pArea;
        ClCrowdManager *pCrowdManager;
        ClSimpleGUI *pGUI;
        sf::VideoMode Mode;

        sf::Clock elapsedTime;
};

#endif // SIMULATION_HPP_INCLUDED
