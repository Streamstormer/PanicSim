/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creation of statistic menu, two buttons and labels with according string, handling button pressure
---------------------------------------------------------------------------------------------------------------------------------------
*/

#ifndef CLSIMPLESTATISTICSMENU_HPP_INCLUDED
#define CLSIMPLESTATISTICSMENU_HPP_INCLUDED

#include "SimpleMenu.hpp"

class ClSimpleStatisticsMenu : public ClSimpleMenu
{
    public:
        ClSimpleStatisticsMenu(enum GameStates myState, sf::Font *pFont, sf::Vector2f screenSize);
        ~ClSimpleStatisticsMenu();
        void draw(sf::RenderWindow &window) const;
        enum GameStates execute(enum Buttons btn) const;
        virtual enum GameStates update(sf::RenderWindow &window, bool mouseReleased) const;
    private:
        void createMenu();
        sf::Texture texture;
        ClSimpleButton *pButton;
        ClSimpleLabel *pLabel;
        sf::Text text;
        std::vector<sf::Text> TextVector;
        const static int LABELSIZE_X = 400;
        const static int LABELSIZE_Y = 80;
};
#endif // CLSIMPLESTATISTICSMENU_HPP_INCLUDED
