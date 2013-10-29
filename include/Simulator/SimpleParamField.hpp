/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Patrick Senneka und Victor Schwartz
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creates a label and two buttons to set the "Besucheranzahl"
---------------------------------------------------------------------------------------------------------------------------------------
*/
#ifndef SimpleParamField_HPP_INCLUDED
#define SimpleParamField_INCLUDED

#include "SimpleLabel.hpp"
#include "SimpleButton.hpp"
#include <SFML/Graphics.hpp>

class ClSimpleParamField
{
public:
    ClSimpleParamField(const sf::Vector2f & position, const sf::Vector2f & buttonSize,const sf::Vector2f & labelSize , sf::Font *pFont);
    ~ClSimpleParamField();

    int getValue();
    void draw(sf::RenderWindow& window);
    void update(bool mouseButtonReleased, sf::RenderWindow& window);

private:
    void create();
    int value;
    sf::Font *pFont;

    sf::Texture texture;
    sf::Vector2f position;

    sf::Vector2f buttonSize;
    ClSimpleButton* buttonPlus;
    ClSimpleButton* buttonMinus;

    sf::Vector2f labelSize;
    ClSimpleLabel* label;
};
#endif // PATH_HPP_INCLUDED
