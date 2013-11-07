#ifndef CLSIMPLESTATISTICSMENU_HPP_INCLUDED
#define CLSIMPLESTATISTICSMENU_HPP_INCLUDED

#include "Statistic.hpp"
#include "SimpleMenu.hpp"

class ClSimpleStatisticsMenu : public ClSimpleMenu
{
    public:
        ClSimpleStatisticsMenu(enum GameStates myState, sf::Font *pFont, sf::Vector2f screenSize);
        ~ClSimpleStatisticsMenu();

        void draw(sf::RenderWindow &window) const;
        enum GameStates execute(enum Buttons btn) const;

        //virtual void execute(enum Buttons btn) const = 0;
        virtual enum GameStates update(sf::RenderWindow &window, bool mouseReleased) const;
    private:
        void createMenu();
        sf::Texture texture;
        ClSimpleButton *pButton;
        ClSimpleLabel *pLabel;
        sf::Text text;
        std::vector<sf::Text> TextVector;
};
#endif // CLSIMPLESTATISTICSMENU_HPP_INCLUDED
