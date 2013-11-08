#ifndef SIMPLECREDITSMENU_HPP
#define SIMPLECREDITSMENU_HPP

#include "SimpleMenu.hpp"


class ClSimpleCreditsMenu : public ClSimpleMenu
{
public:
    ~ClSimpleCreditsMenu();
    ClSimpleCreditsMenu(enum GameStates myState, sf::Font *pFont, sf::Vector2f screenSize);
    void draw(sf::RenderWindow &window) const;
    enum GameStates execute(enum Buttons btn) const;

    //virtual void execute(enum Buttons btn) const = 0;
    virtual enum GameStates update(sf::RenderWindow &window, bool mouseReleased) const;
private:
    void createMenu();

    sf::RectangleShape textSpace;
    sf::Color spaceColor;
    sf::Text text;
    sf::String creditText;
    ClSimpleButton *pButton;
};

#endif // SIMPLECREDITSMENU_HPP
