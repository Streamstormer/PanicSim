#ifndef SIMULATION_HPP_INCLUDED
#define SIMULATION_HPP_INCLUDED

#include "../../include/Simulator/Crowd.hpp"
#include "../../include/Simulator/Area.hpp"
#include "../../include/Simulator/CrowdManager.hpp"
#include "../../include/Common/FileHandler.hpp"

class ClSimulation
{
    public:

        ClSimulation(const sf::VideoMode &Mode);
        ~ClSimulation();
        bool update(sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

        static void updateSpeed(bool pause, bool normal, bool fastForward);
    private:

        // FileHandler logic goes here
                              // this function is called in the constructor

        void createObjects();
        // Calculates the offset to enable scrolling
        // called in update
        void calculateOffset(float frameTime);

        ClArea *pArea;
        ClCrowdManager *pCrowdManager;
        sf::VideoMode Mode;
        sf::Clock elapsedTime;
        sf::Vector2f LevelSize;

        // used for scrolling
        sf::View gameView;
        sf::Vector2f currentOffset;
        static int speed;
};

#endif // SIMULATION_HPP_INCLUDED
