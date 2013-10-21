#ifndef SIMPLESTARTMENU_HPP
#define SIMPLESTARTMENU_HPP

#include "SimpleMenu.hpp"

class ClSimpleStartMenu : public ClSimpleMenu
{
    public:
    ~ClSimpleStartMenu();
    ClSimpleStartMenu(enum GameStates myState, sf::Font *pFont, sf::Vector2f screenSize);
    void draw(sf::RenderWindow &window) const;
    enum GameStates execute(enum Buttons btn) const;

    //virtual void execute(enum Buttons btn) const = 0;
    virtual enum GameStates update(sf::RenderWindow &window) const;
    private:
    void createMenu();
};

#endif // SIMPLESTARTMENU_HPP