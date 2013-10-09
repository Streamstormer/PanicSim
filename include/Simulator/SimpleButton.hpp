#ifndef SIMPLE_BUTTON_INCLUDE
#define SIMPLE_BUTTON_INCLUDE
#include <SFML/Graphics.hpp>
#include <iostream>

enum Buttons {HEATMAP = 0, BOMB, STOP, PLAY, FASTFORWARD, FIRE };


class ClSimpleButton
{
    public:
        ClSimpleButton(int id, Buttons button, int GameState, const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale)
        {
            //
            pressed = false;
            this->scale = scale;
            this->GameState = GameState;
            this->ButtonType = button;
            this->id = id;
            Rect.width = newSize.x;
            Rect.height = newSize.y;
            Rect.top = 0;
            Rect.left = 0;

            // Cut the Button of the Picture containing all Buttons
            sf::Vector2f Offset;
            Offset.x = (int)(button%2)*newSize.x;
            Offset.y = (int)(button/2)*newSize.y;
            Rect.top += Offset.y;
            Rect.left += Offset.x;

            // Set Picture with subrect
            ButtonPicture.setTexture(texture);
            ButtonPicture.setTextureRect(Rect);
            ButtonPicture.setScale(scale,scale);

            // set the rect that was misused to the right values
            Rect.top = position.y;
            Rect.left = position.x;
            ButtonPicture.setPosition(position);

            // Additional
            ClickTimer.restart();

            // Debugging
            /*
            std::cout << " --- " << std::endl;
            std::cout << "p.x" << Rect.left;
            std::cout << " p.y " << Rect.top << std::endl;
            std::cout << "w :" << Rect.width;
            std::cout << "h :" << Rect.height;
            std::cout << "----id : " << id << "----" << std::endl;
            */
        }
        bool isPressed(const sf::Vector2i &Mouse)
        {
            if(pressed == false && Rect.contains(Mouse) && ClickTimer.getElapsedTime().asMilliseconds() > 1000)
            {
                ClickTimer.restart();
                pressed = true;
                return true;
            }
            pressed = false;
            return false;
        }
        void draw(sf::RenderWindow& window)
        {
            window.draw(ButtonPicture);
        }
        Buttons getButtonType()
        {
            return ButtonType;
        }
    private:

        sf::Clock ClickTimer;

        bool pressed;
        float scale;
        int id;
        Buttons ButtonType;
        int GameState;
        sf::Rect<int> Rect;
        sf::Sprite ButtonPicture;
};


#endif // SIMPLE_BUTTON_INCLUDE
