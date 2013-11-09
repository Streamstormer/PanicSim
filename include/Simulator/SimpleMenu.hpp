#ifndef SIMPLEMENU_HPP
#define SIMPLEMENU_HPP

#include "Simulation.hpp"
#include "Statistic.hpp"
#include "SimpleButton.hpp"
#include "SimpleLabel.hpp"
#include <vector>

class ClSimpleMenu
{
    public:
        virtual ~ClSimpleMenu(); // virtual dktor for correct memory management
        virtual void draw(sf::RenderWindow &window) const = 0;
        enum GameStates getMyState();
        virtual enum GameStates execute(enum Buttons btn) const = 0;
        virtual enum GameStates update(sf::RenderWindow &window, bool mouseReleased) const = 0;
    protected:
        sf::Font *pFont;
        sf::Sprite myButtons;
        sf::Vector2f screenSize;
        sf::Texture texture;
        enum GameStates myState;

        std::vector<ClSimpleButton *> ButtonVector;
        std::vector<ClSimpleLabel *> LabelVector;
        sf::Texture bg_texture;
        sf::Sprite bg;
        sf::RectangleShape bg_color;
};

#endif // SIMPLEMENU_HPP
