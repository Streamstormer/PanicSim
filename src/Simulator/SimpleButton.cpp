#include "../../include/Simulator/SimpleButton.hpp"


//public:
ClSimpleButton::ClSimpleButton(int id, Buttons button, int PictureID , const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale)
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
ClSimpleButton::~ClSimpleButton()
{
    // CleanUp is done by the OS here
    //delete this->pButtonText;
    //delete this->pText;
}
bool ClSimpleButton::isPressed(sf::RenderWindow & window)
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
void ClSimpleButton::draw(sf::RenderWindow& window)
{
    window.draw(ButtonPicture);
    if(pText != NULL)
    window.draw(*pText);
}
Buttons ClSimpleButton::getButtonType()
{
    return ButtonType;
}

void ClSimpleButton::setText(sf::String buttonText, sf::Font *pFont)
{
    pText = new sf::Text;
    pButtonText = new sf::String(buttonText);
    *this->pButtonText = buttonText;
    this->pText->setString(*this->pButtonText);
    this->pText->setFont(*pFont);
    this->pText->setStyle(sf::Text::Regular);

    this->pText->setCharacterSize(60);
    sf::Rect<float> textRect = this->pText->getGlobalBounds();
    this->pText->setPosition(Rect.left + ((Rect.width-textRect.width)/2),Rect.top + (Rect.height-textRect.height)/4);

    this->pText->setColor(sf::Color::White);
}

void ClSimpleButton::lightButtonHover()         // when the mouse hovers over the button
{
    sf::Color color(255,255,255);
    ButtonPicture.setColor(color);
}
void ClSimpleButton::darkenButtonPressed()      // when the mouse presses the button
{
    sf::Color color(120,120,120);
    ButtonPicture.setColor(color);
}
