#include "../../include/Simulator/SimpleButton.hpp"


//public:
ClSimpleButton::ClSimpleButton(int id, Buttons button, int PictureID ,int GameState, const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale)
{
    //
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
    Offset.x = (int)(PictureID%2)*newSize.x;
    Offset.y = (int)(PictureID/2)*newSize.y;
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

    // scale the rect correctly
    Rect.width *= scale;
    Rect.height *= scale;

    // set sf::Text to not drawn

    pFont = NULL;
    buttonText.clear();
    text.setString(buttonText);
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
ClSimpleButton::~ClSimpleButton() {}
bool ClSimpleButton::isPressed(sf::RenderWindow & window)
{
    if( Rect.contains(sf::Mouse::getPosition(window)))
    {
        return true;
    }
    return false;
}
void ClSimpleButton::draw(sf::RenderWindow& window)
{
    window.draw(ButtonPicture);
    window.draw(text);
}
Buttons ClSimpleButton::getButtonType()
{
    return ButtonType;
}

void ClSimpleButton::setText(const sf::String &buttonText, sf::Font *pFont)
{
    this->buttonText = buttonText;
    this->text.setString(this->buttonText);
    this->text.setFont(*pFont);
    this->text.setStyle(sf::Text::Regular);

    this->text.setCharacterSize(60);
    sf::Rect<float> textRect = this->text.getGlobalBounds();
    this->text.setPosition(Rect.left + ((Rect.width-textRect.width)/2),Rect.top + (Rect.height-textRect.height)/4);

    this->text.setColor(sf::Color::White);
}


