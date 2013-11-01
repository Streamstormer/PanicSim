#include "../../include/Simulator/SimpleCreditsMenu.hpp"

ClSimpleCreditsMenu::ClSimpleCreditsMenu(enum GameStates myState, sf::Font *pFont, sf::Vector2f screenSize)
{
   this->myState= myState;
   this->pFont = pFont;
   this->screenSize = screenSize;
   texture.loadFromFile("pictures/Button.png");
   createMenu();
}


ClSimpleCreditsMenu::~ClSimpleCreditsMenu()
{
    delete pButton;

}

void ClSimpleCreditsMenu::createMenu()
    {
        // ClSimpleButton(int id, Buttons button, int GameState, const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale)


        sf::Vector2f position;
        sf::Vector2f buttonSize;
        sf::Vector2f labelSize(200,220);
        buttonSize.x = (float)texture.getSize().x;
        buttonSize.y = (float)texture.getSize().y;

        int id = 0;

        // add centered Buttons
        // Start Button

        position.x = screenSize.x / 2;
        position.x -= buttonSize.x / 2;
        position.y = screenSize.y / 8;

      //  ButtonVector.push_back(pButton);

        textSpace.setPosition(position);
        textSpace.setSize(labelSize);
        spaceColor.r = spaceColor.g = spaceColor.b= 255;
        spaceColor.a = 50;



        textSpace.setFillColor(spaceColor);
        text.setPosition(position.x +labelSize.x/4,position.y);
        creditText= "Credits";
        text.setColor(sf::Color::Red);
        text.setFont(*pFont);
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Regular);
        text.setString(creditText+"\n Lukas\n Benedikt\n Melanie\n Patrick\n Victor");


         position.y += labelSize.y;
        pButton = new ClSimpleButton(id, EXITMENU, 0, texture, buttonSize,position, 1.0f);

        pButton->setText(sf::String("ZURÜCK"),pFont);








    }


    void ClSimpleCreditsMenu::draw(sf::RenderWindow &window) const
    {
        window.draw(textSpace);
        window.draw(text);
        pButton->draw(window);

    }
     enum GameStates ClSimpleCreditsMenu::execute(enum Buttons btn) const
    {
        switch(btn)
        {
        case(MENU):
            {
                return MENU;
            }
        }
        return CREDITSMENU;
    }


   enum GameStates ClSimpleCreditsMenu::update(sf::RenderWindow &window, bool mouseReleased) const
    {


                    if (pButton->isPressed(window))
                    {
                        if(mouseReleased)
                    {

                        return MENU;
                    }
                    }

        //update of paramField

        return CREDITSMENU;

    }
