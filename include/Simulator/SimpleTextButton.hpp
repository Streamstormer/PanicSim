#ifndef SIMPLE_TEXT_BUTTON_INCLUDE
#define SIMPLE_TEXT_BUTTON_INCLUDE
#include <SFML/Graphics.hpp>
#include <iostream>
#include "SimpleIconButton.hpp"

//enum Buttons {HEATMAP = 0, BOMB, STOP, PLAY, FASTFORWARD, FIRE, START, CREDITS, EXIT, PLUS, MINUS, EXITMENU, EXPLOSION };


class ClSimpleTextButton : public ClSimpleIconButton
{
    public:
        ClSimpleTextButton(int id, Buttons button, int PictureID , const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale);
        ~ClSimpleTextButton();

        void setText(sf::String buttonText, sf::Font *pFont);


    private:

        float scale;
        int id;
        Buttons ButtonType;

        sf::String *pButtonText;
        sf::Text *pText;
        sf::Font *pFont;
        sf::Rect<int> Rect;
        sf::Sprite ButtonPicture;
};


#endif // SIMPLE_TEXT_BUTTON_INCLUDE
