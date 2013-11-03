#ifndef SIMULATION_HPP_INCLUDED
#define SIMULATION_HPP_INCLUDED

#include "Crowd.hpp"
#include "Area.hpp"
#include "CrowdManager.hpp"
#include "ThreatManager.hpp"
#include "../../include/Common/FileHandler.hpp"

enum GameStates {MENU, SIMULATION, PAUSE, EXITSTATE, CREDITSMENU};

class ClSimulation
{
    public:

        ClSimulation(const sf::VideoMode &Mode);
        ~ClSimulation();
        bool update(sf::RenderWindow &window, bool mouseReleased);
        void draw(sf::RenderWindow &window);

        void setCurGameState(enum GameStates newGS)
        {
            curGameState = newGS;
        }


        static void updateSpeed(bool pause, bool normal, bool fastForward);
    private:

        // FileHandler logic goes here
        // to read the Level Meta Data
        // called in the constructor
        //void readLevelMetaData( );
        //void setLevelMetaData(sf::Vector2f *pLevelSize, sf::Color *pColor);

        // FileHandler logic goes here
        // this function is called in the constructor

        void createObjects();
        // Calculates the offset to enable scrolling
        // called in update
        void calculateOffset(float frameTime);

        void partitionCrowds(int totalVisitors);

        void calculatePriorities(int *sum, int *priority, int counter);


        ClArea *pArea;
        ClCrowdManager *pCrowdManager;
        ClThreatManager *pThreatManager;
        sf::VideoMode Mode;
        sf::Clock elapsedTime;
        sf::Vector2i levelSize;

        // used for scrolling
        sf::View gameView;
        sf::Vector2f currentOffset;
        static int speed;

        enum GameStates curGameState;

        //Background Color
        //sf::Color bgColor;
};

#endif // SIMULATION_HPP_INCLUDED
