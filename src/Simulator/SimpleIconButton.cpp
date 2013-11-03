#include "../../include/Simulator/SimpleIconButton.hpp"


//public:
ClSimpleIconButton::ClSimpleIconButton(int id, Buttons button, int PictureID , const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale)
{
    //
    this->scale = scale;
    this->ButtonType = button;
    this->id = id;
    Rect.width = newSize.x;
    Rect.height = newSize.y;
    Rect.top = 0;
    Rect.left = 0;

    // Cut the Button of the Picture containing all Buttons
    sf::Vector2f Offset;
    Offset.x = (int)(PictureID%2)*newSize.x;
    Offset.y = (int)(PictureID/2)*newSize.y;
    Rect.top += Offset.y;
    Rect.left += Offset.x;

    // Set Picture with subrect
    ButtonPicture.setTexture(texture);
    ButtonPicture.setTextureRect(Rect);
    ButtonPicture.setScale(scale,scale);
    ButtonPicture.setColor( sf::Color(160,160,160) );

    // set the rect that was misused to the right values
    Rect.top = position.y;
    Rect.left = position.x;
    ButtonPicture.setPosition(position);

    // scale the rect correctly
    Rect.width *= scale;
    Rect.height *= scale;

    // set sf::Text to not drawn

    pFont = NULL;
    pText = NULL;

    // Debugging
    /*
    std::cout << " --- " << std::endl;
    std::cout << "p.x " << Rect.left;
    std::cout << "p.y " << Rect.top << std::endl;
    std::cout << "w : " << Rect.width;
    std::cout << "h : " << Rect.height;
    std::cout << "----id : " << id << "----" << std::endl;
    */
}
ClSimpleIconButton::~ClSimpleIconButton()
{
    // CleanUp is done by the OS here
    //delete this->pButtonText;
    //delete this->pText;
}
bool ClSimpleIconButton::isPressed(sf::RenderWindow & window)
{
    ButtonPicture.setColor(sf::Color(180,180,180));
    if( Rect.contains(sf::Mouse::getPosition(window)))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            darkenButtonPressed();
        }
        else
            lightButtonHover();
        return true;
    }
    return false;
}
void ClSimpleIconButton::draw(sf::RenderWindow& window)
{
    window.draw(ButtonPicture);
    if(pText != NULL)
    window.draw(*pText);
}
Buttons ClSimpleIconButton::getButtonType()
{
    return ButtonType;
}



void ClSimpleIconButton::lightButtonHover()         // when the mouse hovers over the button
{
    sf::Color color(255,255,255);
    ButtonPicture.setColor(color);
}
void ClSimpleIconButton::darkenButtonPressed()      // when the mouse presses the button
{
    sf::Color color(120,120,120);
    ButtonPicture.setColor(color);
}
