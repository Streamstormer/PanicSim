#include "../../include/Simulator/SimpleStatisticsMenu.hpp"

ClSimpleStatisticsMenu::ClSimpleStatisticsMenu(enum GameStates myState, sf::Font *pFont, sf::Vector2f screenSize)
{
    this->myState= myState;
    this->pFont = pFont;
    this->screenSize = screenSize;
 //   texture.loadFromFile("pictures/Button.png");
    texture.loadFromFile("pictures/ButtonSet1.png");
    createMenu();
}

ClSimpleStatisticsMenu::~ClSimpleStatisticsMenu(){}

void ClSimpleStatisticsMenu::createMenu()
{
    // ClSimpleButton(int id, Buttons button, int GameState, const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale)
    sf::Vector2f labelSize;
    labelSize.x = 400;
    labelSize.y = 100;

    sf::Vector2f buttonSize;
    buttonSize.x = texture.getSize().x;
    buttonSize.y = texture.getSize().y;
    buttonSize.x /=2;
    buttonSize.y /=4;

    sf::Vector2f bg_size;
    bg_size.x = screenSize.x/2;
    bg_size.y = screenSize.y;

    sf::Color bgColor(0,0,0, 70);
    bg_color.setSize(bg_size);
    bg_color.setFillColor(bgColor);
    bg_color.setPosition(2*screenSize.x/3,0);

    sf::Vector2f position;
    position.x = 0.9*screenSize.x;
    position.x -= buttonSize.x;
    position.y = 3*screenSize.y/4;

    float scale = 0.5;
    int id = 0;

    // add EXITMENU Button
    pButton = new ClSimpleButton(id, EXITMENU, 7, texture, buttonSize, position, scale);
    ButtonVector.push_back(pButton);

    // add DIAGRAMM Button
    id++;
    position.x += buttonSize.x;
    pButton = new ClSimpleButton(id, DIAGRAMM, 6, texture, buttonSize, position, scale);
    ButtonVector.push_back(pButton);

    // add LABEL "Number of Bombs"
    position.x = 2*screenSize.x/3;
    position.y = screenSize.y/20;
    pLabel = new ClSimpleLabel(position, labelSize,sf::String("Anzahl an Bomben"), *pFont, ClStatistic::getNumberBomb());
    LabelVector.push_back(pLabel);

    // add LABEL "casualties by bombs"
    position.y += labelSize.y + 1;
    pLabel = new ClSimpleLabel(position, labelSize, sf::String("Opfer von Bomben"), *pFont, ClStatistic::getNumberKillsBomb());
    LabelVector.push_back(pLabel);

    // add LABEL "Number of Fire"
    position.y += labelSize.y + 1;
    pLabel = new ClSimpleLabel(position, labelSize, sf::String("Anzahl an Feuer"), *pFont, ClStatistic::getNumberFire());
    LabelVector.push_back(pLabel);

    // add LABEL "casualties by fire"
    position.y += labelSize.y + 1;
    pLabel = new ClSimpleLabel(position, labelSize, sf::String("Opfer von Feuern"), *pFont, ClStatistic::getNumberKillsFire());
    LabelVector.push_back(pLabel);

    // add LABEL "evacuation time"
    position.y += labelSize.y + 1;
    pLabel = new ClSimpleLabel(position, labelSize, sf::String("Zeit für Evakuierung in s"), *pFont, ClStatistic::getTime());
    LabelVector.push_back(pLabel);
}

void ClSimpleStatisticsMenu::draw(sf::RenderWindow &window) const
{
    window.draw(bg_color);
    for(unsigned int n=0; n<LabelVector.size(); n++)
    {
        LabelVector[n]->draw(window);
    }
    for(unsigned int m=0; m<ButtonVector.size(); m++)
    {
        ButtonVector[m]->draw(window);
    }
}

enum GameStates ClSimpleStatisticsMenu::execute(enum Buttons btn) const
{
    switch(btn)
    {
    case(EXITMENU):
        {
            ClStatistic::setInStatistic(false);
            ClStatistic::setDoDrawStatistic(false);
            return SIMULATION;
        }break;
    case(DIAGRAMM):
        {
            ClStatistic::setInStatistic(false);
            ClStatistic::setDoDrawStatistic(false);
            ClStatistic::toggleDiagrammDraw();
        }break;
    }
    return STATISTICS;
}

enum GameStates ClSimpleStatisticsMenu::update(sf::RenderWindow &window, bool mouseReleased) const
{
    for (unsigned int n = 0; n<ButtonVector.size(); n++)
    {
        if (ButtonVector[n]->isPressed(window))
        {
            if(mouseReleased == true)
            {
                return execute(ButtonVector[n]->getButtonType());
            }
        }
    }
    return STATISTICS;
}
