/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Lukas
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    Overlay during SIMULATION
---------------------------------------------------------------------------------------------------------------------------------------
*/


#ifndef SIMPLESIMULATIONMENU_HPP
#define SIMPLESIMULATIONMENU_HPP
#include "SimpleMenu.hpp"

class ClSimpleSimulationMenu : public ClSimpleMenu
{
     public:
    ~ClSimpleSimulationMenu() {}
    ClSimpleSimulationMenu(enum GameStates myState, sf::Font *pFont, sf::Vector2f screenSize);
    void draw(sf::RenderWindow &window) const;
    virtual enum GameStates execute(enum Buttons btn) const;
    virtual enum GameStates update(sf::RenderWindow &window, bool mouseReleased) const;

        private:
    void createMenu();
    sf::Texture texture2;
    sf::Texture texture3;
};
#endif // SIMPLESIMULATIONMENU_HPP
