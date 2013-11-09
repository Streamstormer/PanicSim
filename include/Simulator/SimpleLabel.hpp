#ifndef SIMPLELABEL_HPP_INCLUDED
#define SIMPLELABEL_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>


class ClSimpleLabel
{
    public:
    ClSimpleLabel(const sf::Vector2f &position, const sf::Vector2f &labelSize, const sf::String &labelText, const sf::Font &font, int *pNumber);

    ~ClSimpleLabel() {}
    void draw(sf::RenderWindow& window);

    private:
    sf::Vector2f position;
    sf::Vector2f labelSize;
    sf::String labelText;
    sf::Font font;
    int *pNumber;

    sf::RectangleShape textSpace;
    sf::Color spaceColor;
    sf::Text text;
    sf::String title;
    sf::String number;
};

#endif // SIMPLELABEL_HPP_INCLUDED
