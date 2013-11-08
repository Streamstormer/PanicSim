#include "../../include/Simulator/SimpleStatisticsMenu.hpp"

ClSimpleStatisticsMenu::ClSimpleStatisticsMenu(enum GameStates myState, sf::Font *pFont, sf::Vector2f screenSize)
{
    this->myState= myState;
    this->pFont = pFont;
    this->screenSize = screenSize;
    texture.loadFromFile("pictures/Button.png");
    createMenu();
}

ClSimpleStatisticsMenu::~ClSimpleStatisticsMenu()
{
    delete pButton;
}

void ClSimpleStatisticsMenu::createMenu()
{
    // ClSimpleButton(int id, Buttons button, int GameState, const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale)
    sf::Vector2f position;
    sf::Vector2f buttonSize;
    sf::Vector2f labelSize(400,100);
    buttonSize.x = (float)texture.getSize().x;
    buttonSize.y = (float)texture.getSize().y;
    bg_color.setPosition(2*screenSize.x/3,0);

    sf::Vector2f bg_size;
    bg_size.x = screenSize.x/2;
    bg_size.y = screenSize.y;
    bg_color.setSize(bg_size);

    sf::Color bgColor(0,0,0, 70);
    bg_color.setFillColor(bgColor);

    position.x = 0.9*screenSize.x;
    position.x -= buttonSize.x;
    position.y = 3*screenSize.y/4;

    pButton = new ClSimpleButton(0, EXITMENU, 0, texture, buttonSize, position, 1.0f);
    pButton->setText(sf::String("MENU"),pFont);

    position.x = 2*screenSize.x/3;
    position.y = screenSize.y/20;
    pLabel = new ClSimpleLabel(position, labelSize,sf::String("Number of Bombs:"), *pFont, ClStatistic::getNumberBomb());
    LabelVector.push_back(pLabel);

    position.y += labelSize.y + 1;
    pLabel = new ClSimpleLabel(position, labelSize, sf::String("Number of Fire:"), *pFont, ClStatistic::getNumberFire());
    LabelVector.push_back(pLabel);

    position.y += labelSize.y + 1;
    pLabel = new ClSimpleLabel(position, labelSize, sf::String("People killed by fire:"), *pFont, ClStatistic::getNumberKillsFire());
    LabelVector.push_back(pLabel);

    position.y += labelSize.y + 1;
    pLabel = new ClSimpleLabel(position, labelSize, sf::String("People killed by bombs:"), *pFont, ClStatistic::getNumberKillsBomb());
    LabelVector.push_back(pLabel);

    position.y += labelSize.y + 1;
    pLabel = new ClSimpleLabel(position, labelSize, sf::String("Evacuation-Time in sec:"), *pFont, ClStatistic::getTime());
    LabelVector.push_back(pLabel);
}

void ClSimpleStatisticsMenu::draw(sf::RenderWindow &window) const
{
    window.draw(bg_color);
    for(unsigned int n=0; n<LabelVector.size(); n++)
    {
        LabelVector[n]->draw(window);
    }
    pButton->draw(window);
}

enum GameStates ClSimpleStatisticsMenu::execute(enum Buttons btn) const
{
    switch(btn)
    {
    case(MENU):
        {
            return MENU;
        }
    }
    return STATISTICS;
}


enum GameStates ClSimpleStatisticsMenu::update(sf::RenderWindow &window, bool mouseReleased) const
{
    if (pButton->isPressed(window))
    {
        if(mouseReleased)
        {
            return MENU;
        }
    }
    return STATISTICS;
}
