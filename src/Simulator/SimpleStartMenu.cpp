#include "../../include/Simulator/SimpleStartMenu.hpp"

ClSimpleStartMenu::~ClSimpleStartMenu()
{
    for(unsigned int n = 0; n<ButtonVector.size();n++)
    {
        delete ButtonVector[n];
    }
}
void ClSimpleStartMenu::createMenu()
    {
        // ClSimpleButton(int id, Buttons button, int GameState, const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale)

        ClSimpleButton *pButton;
        sf::Vector2f position;
        sf::Vector2f buttonSize;
        buttonSize.x = (float)texture.getSize().x;
        buttonSize.y = (float)texture.getSize().y;

        int id = 0;

        // add centered Buttons
        // Start Button

        position.x = screenSize.x / 2;
        position.x -= buttonSize.x / 2;
        position.y = screenSize.y / 8;
        pButton = new ClSimpleButton(id, START, 0,MENU, texture, buttonSize,position, 1.0f);
        pButton->setText(sf::String("Start"),pFont);
        ButtonVector.push_back(pButton);

        // Credits Button

        position.y += buttonSize.y * 1.5f;
        pButton = new ClSimpleButton(id, CREDITS,0, MENU, texture, buttonSize,position, 1.0f);
        pButton->setText(sf::String("Credits"),pFont);
        ButtonVector.push_back(pButton);

        // Exit Button

        position.y += buttonSize.y * 1.5f;
        pButton = new ClSimpleButton(id,EXIT,0,MENU,texture,buttonSize,position,1.0f);
        pButton->setText(sf::String("Exit"),pFont);
        ButtonVector.push_back(pButton);
    }

    ClSimpleStartMenu::ClSimpleStartMenu(enum GameStates myState, sf::Font *pFont, sf::Vector2f screenSize)
    {
        this->myState = myState;
        this->pFont = pFont;
        this->screenSize = screenSize;
        texture.loadFromFile("pictures/Button.png");
        createMenu();
    }
    void ClSimpleStartMenu::draw(sf::RenderWindow &window) const
    {
        for(int n = 0; n < ButtonVector.size();n++)
        {
            ButtonVector[n]->draw(window);
        }
    }
     enum GameStates ClSimpleStartMenu::execute(enum Buttons btn) const
    {
        switch(btn)
        {
        case(START):
            {
                return SIMULATION;
            }break;
        case(EXIT) :
            {
                return EXITSTATE;
            }break;
        case(CREDITS) :
            {
                std::cout << "CREDITS" << std::endl;
            }break;
        }
        return MENU;
    }


    enum GameStates ClSimpleStartMenu::update(sf::RenderWindow &window, bool mouseReleased) const
    {
        if(mouseReleased)
        {
                for (unsigned int n = 0;n<ButtonVector.size();n++)
                {
                    if (ButtonVector[n]->isPressed(window))
                    {
                        return execute(ButtonVector[n]->getButtonType());
                    }
                }
        }
        return MENU;

    }
