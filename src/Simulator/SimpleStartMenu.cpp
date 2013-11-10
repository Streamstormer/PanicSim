#include "../../include/Simulator/SimpleStartMenu.hpp"

ClSimpleStartMenu::~ClSimpleStartMenu()
{
    for(unsigned int n = 0; n<ButtonVector.size(); n++)
    {
        // FIXME: Workaround for crash
        //     delete ButtonVector[n];
    }
}

void ClSimpleStartMenu::createMenu()
{
    // ClSimpleButton(int id, Buttons button, int GameState, const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale)

    ClSimpleButton *pButton;
    sf::Vector2f position;
    sf::Vector2f buttonSize;
    sf::Vector2f labelSize(200,160);
    buttonSize.x = (float)texture.getSize().x;
    buttonSize.y = (float)texture.getSize().y;
    int id = 0;
    bg.setPosition((4*screenSize.x/5)-(bg_texture.getSize().x/2), screenSize.y/9);
    bg.setTexture(bg_texture);
    bg_color.setPosition(0,0);
    bg_color.setSize(screenSize);
    sf::Color bgColor(190,190,190);
    bg_color.setFillColor(bgColor);

    // Start Button
    position.x = screenSize.x/3;
    position.x -= labelSize.x/2;
    position.y = 3*screenSize.y/5;
    pButton = new ClSimpleButton(id, START, 0, texture, buttonSize,position, 1.0f);
    pButton->setText(sf::String("Start"),pFont);
    ButtonVector.push_back(pButton);

    //Param Field
    position.y = screenSize.y/7;
    paramField = new ClSimpleParamField(position,buttonSize,labelSize, pFont);

    // Credits Button
    position.x = 4*screenSize.x/5;
    position.x -= labelSize.x/2;
    position.y = screenSize.y/3+labelSize.y/2;
    pButton = new ClSimpleButton(id, CREDITS,0, texture, buttonSize,position, 1.0f);
    pButton->setText(sf::String("Credits"),pFont);
    ButtonVector.push_back(pButton);

    // Exit Button
    position.y = 3*screenSize.y/5;
    pButton = new ClSimpleButton(id,EXIT,0,texture,buttonSize,position,1.0f);
    pButton->setText(sf::String("Exit"),pFont);
    ButtonVector.push_back(pButton);
}

ClSimpleStartMenu::ClSimpleStartMenu(enum GameStates myState, sf::Font *pFont, sf::Vector2f screenSize)
{
    this->myState = myState;
    this->pFont = pFont;
    this->screenSize = screenSize;
    texture.loadFromFile("pictures/Button.png");
    bg_texture.loadFromFile("pictures/PanicSoft.png");
    createMenu();
}

void ClSimpleStartMenu::draw(sf::RenderWindow &window) const
{
    window.draw(bg_color);
    window.draw(bg);
    for(int n = 0; n < ButtonVector.size(); n++)
    {
        ButtonVector[n]->draw(window);
    }
    paramField->draw(window);
}

enum GameStates ClSimpleStartMenu::execute(enum Buttons btn) const
{
    switch(btn)
    {
    case(START):
        {
            ClStatistic::reset();
            return SIMULATION;
        }
        break;
    case(EXIT) :
    {
        return EXITSTATE;
    }
    break;
    case(CREDITS) :
    {
        return CREDITSMENU;
    }
    break;
    }
    return MENU;
}

enum GameStates ClSimpleStartMenu::update(sf::RenderWindow &window, bool mouseReleased) const
{
    for (unsigned int n = 0; n<ButtonVector.size(); n++)
    {
        if (ButtonVector[n]->isPressed(window))
        {
            if(mouseReleased)
                return execute(ButtonVector[n]->getButtonType());
        }
    }
    //update of paramField
    paramField->update(mouseReleased, window);
    ClSimulation::setTotalVisitors(paramField->getValue());
    return MENU;
}
