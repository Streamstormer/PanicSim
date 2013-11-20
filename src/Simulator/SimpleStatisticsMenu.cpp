/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Melanie Hammerschmidt
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creation of statistic menu, two buttons and labels with according string, handling button pressure
---------------------------------------------------------------------------------------------------------------------------------------
*/

#include "../../include/Simulator/SimpleStatisticsMenu.hpp"

ClSimpleStatisticsMenu::ClSimpleStatisticsMenu(enum GameStates myState, sf::Font *pFont, sf::Vector2f screenSize)
{
    this->myState= myState;
    this->pFont = pFont;
    this->screenSize = screenSize;

    //load button textures
    texture.loadFromFile("pictures/ButtonSet1.png");
    //create statistic menu
    createMenu();
}

ClSimpleStatisticsMenu::~ClSimpleStatisticsMenu(){}

void ClSimpleStatisticsMenu::createMenu()
{
    // background bg_color with size, color and position
    sf::Vector2f bg_size;
    bg_size.x = 3*screenSize.x/5;
    bg_size.y = screenSize.y;

    sf::Color bgColor(0,0,0, 70);

    sf::Vector2f bg_position(2*screenSize.x/3,0);

    bg_color.setSize(bg_size);
    bg_color.setFillColor(bgColor);
    bg_color.setPosition(bg_position);

    // prototype: ClSimpleButton(int id, Buttons button, int PictureID , const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale)
    sf::Vector2f buttonSize;
    buttonSize.x = texture.getSize().x;
    buttonSize.y = texture.getSize().y;
    buttonSize.x /=2;
    buttonSize.y /=4;

    sf::Vector2f position;
    position.x = 0.9*screenSize.x;
    position.x -= buttonSize.x;
    position.y = 4*screenSize.y/5-buttonSize.y/3;

    float scale = 0.5;
    int id = 0;

    // add DIAGRAMM Button
    pButton = new ClSimpleButton(id, DIAGRAMM, 6, texture, buttonSize, position, scale);
    ButtonVector.push_back(pButton);

    // add EXITMENU Button
    id++;
    position.x += buttonSize.x;
    pButton = new ClSimpleButton(id, EXITMENU, 7, texture, buttonSize, position, scale);
    ButtonVector.push_back(pButton);

    // prototype: ClSimpleLabel(const sf::Vector2f &position, const sf::Vector2f &labelSize, const sf::String &labelText, const sf::Font &font, int *pNumber)
    sf::Vector2f labelSize;
    labelSize.x = LABELSIZE_X;
    labelSize.y = LABELSIZE_Y;

    // add LABEL "Number of Bombs"
    position.x = 2*screenSize.x/3;
    position.y = screenSize.y/30;
    sf::String labelText("Anzahl an Bomben");

    pLabel = new ClSimpleLabel(position, labelSize, labelText, *pFont, ClStatistic::getNumberBomb());
    LabelVector.push_back(pLabel);

    // add LABEL "casualties by bombs"
    position.y += labelSize.y;
    labelText = "Opfer von Bomben";

    pLabel = new ClSimpleLabel(position, labelSize, labelText, *pFont, ClStatistic::getNumberKillsBomb());
    LabelVector.push_back(pLabel);

    // add LABEL "Number of Fire"
    position.y += labelSize.y+4;
    labelText = "Anzahl an Feuer";

    pLabel = new ClSimpleLabel(position, labelSize, labelText, *pFont, ClStatistic::getNumberFire());
    LabelVector.push_back(pLabel);

    // add LABEL "casualties by fire"
    position.y += labelSize.y;
    labelText = "Opfer von Feuern";

    pLabel = new ClSimpleLabel(position, labelSize, labelText, *pFont, ClStatistic::getNumberKillsFire());
    LabelVector.push_back(pLabel);

    // add LABEL "casualties by pressure"
    position.y += labelSize.y+4;
    labelText = "Opfer von Druck";

    pLabel = new ClSimpleLabel(position, labelSize, labelText, *pFont, ClStatistic::getNumberKillsPressure());
    LabelVector.push_back(pLabel);

    // add LABEL "evacuation time"
    position.y += labelSize.y+20;
    labelText = "Zeit in Sekunden";

    pLabel = new ClSimpleLabel(position, labelSize, labelText, *pFont, ClStatistic::getTime());
    LabelVector.push_back(pLabel);
}

void ClSimpleStatisticsMenu::draw(sf::RenderWindow &window) const
{
    //draw background color
    window.draw(bg_color);
    //draw all created labels
    for(unsigned int n=0; n<LabelVector.size(); n++)
    {
        LabelVector[n]->draw(window);
    }
    //draw all created buttons
    for(unsigned int m=0; m<ButtonVector.size(); m++)
    {
        ButtonVector[m]->draw(window);
    }
}

enum GameStates ClSimpleStatisticsMenu::execute(enum Buttons btn) const
{
    //1. handling button action
    //2. exit button - return to simulation menu (continue calculations in statistic)
    //3. diagramm button - activate or deactivate diagramm drawing - return to statistics

    //1.
    switch(btn)
    {
        //2.
        case(EXITMENU):
        {
            ClStatistic::setDoDrawStatistic(false);
            return SIMULATION;
        }break;
        //3.
        case(DIAGRAMM):
        {
            ClStatistic::toggleDiagrammDraw();
        }break;

    default: break;
    }
    return STATISTICS;
}

enum GameStates ClSimpleStatisticsMenu::update(sf::RenderWindow &window, bool mouseReleased) const
{
    //update statistic menu - execution of pressed buttons
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
    //if execution doesn´t change game state - return to statistics
    return STATISTICS;
}
