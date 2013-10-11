#ifndef SIMPLELABEL_HPP_INCLUDED
#define SIMPLELABEL_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>

class ClSimpleLabel
{
    public:
    ClSimpleLabel(const sf::Vector2f &position, const sf::Vector2f &labelSize, const sf::String &labelText,int *pNumber);
    //ClSimpleLabel(const sf::Vector2f &position, const sf::Vector2f &labelSize);

    ~ClSimpleLabel() {}
    void draw(sf::RenderWindow& window);

    private:
    sf::Vector2f position;
    sf::Vector2f labelSize;
    sf::String labelText;
    int *pNumber;

    sf::RectangleShape textSpace;
    sf::Color spaceColor;
    sf::Text text;
    sf::String title;
    sf::Font font;
    sf::String number;
};

#endif // SIMPLELABEL_HPP_INCLUDED
