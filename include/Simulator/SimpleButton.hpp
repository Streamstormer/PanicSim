/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Lukas
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    Simple Class that represents a button on screen
---------------------------------------------------------------------------------------------------------------------------------------
*/




#ifndef SIMPLE_BUTTON_INCLUDE
#define SIMPLE_BUTTON_INCLUDE
#include <SFML/Graphics.hpp>
#include <iostream>

enum Buttons {HEATMAP = 0, BOMB, STOP, PLAY, FASTFORWARD, FIRE, START, CREDITS, EXIT, PLUS, MINUS, EXITMENU, EXPLOSION, STATISTIC, DIAGRAMM};


class ClSimpleButton
{
    public:
        ClSimpleButton(int id, Buttons button, int PictureID , const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale);
        ~ClSimpleButton();

        bool isPressed(sf::RenderWindow & window);
        void lightButtonHover();         // when the mouse hovers over the button
        void darkenButtonPressed();      // when the mouse presses the button
        void draw(sf::RenderWindow& window);

        Buttons getButtonType();
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


#endif // SIMPLE_BUTTON_INCLUDE
