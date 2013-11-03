#ifndef SIMPLE_ICON_BUTTON_INCLUDE
#define SIMPLE_ICON_BUTTON_INCLUDE
#include <SFML/Graphics.hpp>
#include <iostream>

enum Buttons {HEATMAP = 0, BOMB, STOP, PLAY, FASTFORWARD, FIRE, START, CREDITS, EXIT, PLUS, MINUS, EXITMENU, EXPLOSION };


class ClSimpleIconButton
{
    public:
        ClSimpleIconButton(int id, Buttons button, int PictureID , const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale);
        ~ClSimpleIconButton();

        bool isPressed(sf::RenderWindow & window);
        void lightButtonHover();         // when the mouse hovers over the button
        void darkenButtonPressed();      // when the mouse presses the button
        void draw(sf::RenderWindow& window);

        Buttons getButtonType();


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


#endif // SIMPLE_ICON_BUTTON_INCLUDE
