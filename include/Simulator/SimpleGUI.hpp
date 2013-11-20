/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Lukas
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    Class that is able to switch between different MENU States as well as handling all the different Menus
---------------------------------------------------------------------------------------------------------------------------------------
*/


#include <SFML/Graphics.hpp>
#ifndef SIMPLE_GUI_INCLUDE
#define SIMPLE_GUI_INCLUDE

#include <vector>
// GUI related
#include "SimpleButton.hpp"
#include "SimpleLabel.hpp"
#include "SimpleStartMenu.hpp"
#include "SimpleSimulationMenu.hpp"
#include "SimpleStatisticsMenu.hpp"

// get static functions for execute from here
#include "HeatMap.hpp"
#include "CrowdManager.hpp"
#include "Simulation.hpp"
#include "SimpleCreditsMenu.hpp"



class ClSimpleGUI
{
public:
    ClSimpleGUI(const sf::Vector2f &ScreenSize);
    ~ClSimpleGUI();

    void draw(sf::RenderWindow &window);
    enum GameStates update( sf::RenderWindow &window, bool mouseReleased);     // executes code when a button is pressed

    GameStates getGameState() {return curState;}


private:


    //void CreateAllLabels();// called in the constructor to create all labels
    void createAllMenus();

    // used for game states :
    std::vector<ClSimpleMenu *> MenuVector;
    ClSimpleMenu * pCurrentMenu;
    GameStates curState;
    ClSimpleStartMenu *pStartMenu;

    // additional information
    sf::Font labelFont;
    sf::Vector2f ScreenSize;
};

#endif // SIMPLE_GUI_INCLUDE
