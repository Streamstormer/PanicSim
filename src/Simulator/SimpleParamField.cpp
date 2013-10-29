/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Patrick Senneka und Victor Schwartz
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creates a label and two buttons to set the "Besucheranzahl"
---------------------------------------------------------------------------------------------------------------------------------------
*/
#include "../../include/Simulator/SimpleParamField.hpp"

ClSimpleParamField::ClSimpleParamField(const sf::Vector2f & position, const sf::Vector2f & buttonSize,const sf::Vector2f & labelSize , sf::Font *pFont)
{
    this->value = 0;
    this->position = position;
    this->pFont = pFont;
    this->buttonSize = buttonSize;
    this->labelSize = labelSize;
    texture.loadFromFile("pictures/ButtonSet2.png");
    create();
}
ClSimpleParamField::~ClSimpleParamField()
{
    delete label;
    delete buttonPlus;
    delete buttonMinus;
    //dtor
}
int ClSimpleParamField::getValue()
{
    return value;
}
void ClSimpleParamField::create()
{

    //ClSimpleLabel::ClSimpleLabel(const sf::Vector2f &position, const sf::Vector2f &labelSize, const sf::String &labelText, const sf::Font &font, int *pNumber)
    label = new ClSimpleLabel(position, labelSize,sf::String("Besucher"), *pFont, &value);

    //ClSimpleButton::ClSimpleButton(int id, Buttons button, int PictureID , const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale)
    position.x += labelSize.x;
    buttonPlus = new ClSimpleButton(0, PLUS, 0, texture,sf::Vector2f(160,160), position, 0.5);
    position.y += 80;
    buttonMinus = new ClSimpleButton(0, MINUS, 1, texture,sf::Vector2f(160,160), position, 0.5);
}
void ClSimpleParamField::draw(sf::RenderWindow& window)
{
    label->draw(window);
    buttonPlus->draw(window);
    buttonMinus->draw(window);
}
void ClSimpleParamField::update(bool mouseButtonReleased, sf::RenderWindow& window)
{
    if(mouseButtonReleased)
    {
        if(buttonMinus->isPressed(window) )
        {
            if(value >= 1000)
            {
                value -= 1000;
            }
        }
        if(buttonPlus->isPressed(window) )
        {
            if(value <= 49000)
            {
                value += 1000;
            }
        }
    }
}
