#include "../../include/Simulator/SimpleLabel.hpp"
#include <sstream>

ClSimpleLabel::ClSimpleLabel(const sf::Vector2f &position, const sf::Vector2f &labelSize,const sf::String &labelText, int *pNumber)
{
    this->position = position;
    this->labelSize = labelSize;
    this->labelText = labelText;
    this->pNumber = pNumber;

    textSpace.setPosition(position);
    textSpace.setSize(labelSize);

    spaceColor.r = spaceColor.g = spaceColor.b = 255;
    spaceColor.a = 50;
    textSpace.setFillColor(spaceColor);

    text.setPosition(position);
    title = labelText;
    text.setColor(sf::Color::Red);

    if(!font.loadFromFile("fonts/LiberationSerif-Regular.ttf"))
    {
        std::cout << "Hallo" << std::endl;
    }
    text.setFont(font);

}


void ClSimpleLabel::draw(sf::RenderWindow& window)
{
    text.setCharacterSize(30);
    text.setStyle(sf::Text::Regular);

    std::stringstream number_ss;
    number_ss << *pNumber;
    number = number_ss.str();

    text.setString(title + "\n" + number);

    window.draw(textSpace);
    window.draw(text);
}
