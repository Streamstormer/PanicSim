#ifndef SIMULATION_HPP_INCLUDED
#define SIMULATION_HPP_INCLUDED

#include "../../include/Simulator/Crowd.hpp"
#include "../../include/Simulator/Area.hpp"
#include "../../include/Simulator/CrowdManager.hpp"
#include "../../include/Simulator/SimpleGUI.hpp"
#include "../../include/Common/FileHandler.hpp"

class ClSimulation
{
    public:

        ClSimulation(const sf::VideoMode &Mode);
        ~ClSimulation();
        bool update(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

    private:

        void createObjects(); // FileHandler logic goes here
                              // this function is called in the constructor

        void calculateOffset(float frameTime); // Calculates the offset to enable scrolling
                                // called in update
        ClArea *pArea;
        ClCrowdManager *pCrowdManager;
        ClSimpleGUI *pGUI;
        sf::VideoMode Mode;
        sf::Clock elapsedTime;
        sf::Vector2f LevelSize;

        // used for scrolling
        sf::View gameView;
        sf::Vector2f currentOffset;
};

#endif // SIMULATION_HPP_INCLUDED
