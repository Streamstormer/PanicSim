#include "../../include/Simulator/SimpleGUI.hpp"

   ClSimpleGUI::ClSimpleGUI(const sf::Vector2f &ScreenSize)
    {
        id = 0;
        this->ScreenSize = ScreenSize;
        ButtonsTexture.loadFromFile("pictures/ButtonSet1.png");

        CreateAllButtons();
    }
    ClSimpleGUI::~ClSimpleGUI()
    {
        for(unsigned int n = 0; n< ButtonVector.size();n++)
        {
            delete ButtonVector[n];
        }
    }

    void ClSimpleGUI::draw(sf::RenderWindow &window)
    {

        for(unsigned int n = 0; n< ButtonVector.size();n++)
        {
            ButtonVector[n]->draw(window);
        }
    }

    void ClSimpleGUI::update( sf::RenderWindow &window)     // executes code when a button is pressed
    {
        for(unsigned int n = 0; n< ButtonVector.size();n++)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(ButtonVector[n]->isPressed(sf::Mouse::getPosition(window)))
                {
                    Execute(ButtonVector[n]->getButtonType());
                }
            }
        }
    }


    void ClSimpleGUI::CreateAllButtons()// called in the constructor to create all buttons
    {
        // add Simulation Buttons
        // add downleft Buttons
        sf::Vector2f ButtonSize(160,160);
        sf::Vector2f Position(0,ScreenSize.y);

        ClSimpleButton *pAddMe;
        float scale = 0.25;

        Position.y -= ButtonSize.y;
        Position.x += ButtonSize.x*0.25;

        // ClSimpleButton(int id, Buttons button, int GameState, const sf::Texture &texture, const sf::Vector2f &newSize, const sf::Vector2f& position, float scale)

        // add STOP Button
        id++;
        pAddMe = new ClSimpleButton(id, STOP, SIMULATION, ButtonsTexture, ButtonSize, Position, scale);
        ButtonVector.push_back(pAddMe);
        // add PLAY Button
         Position.x+=ButtonSize.x*1.5*scale;
        id++;
        pAddMe = new ClSimpleButton(id, PLAY, SIMULATION, ButtonsTexture, ButtonSize, Position, scale);
        ButtonVector.push_back(pAddMe);
        // add FASTFORWARD Button
        Position.x+=ButtonSize.x*1.5*scale;
        id++;
        pAddMe = new ClSimpleButton(id, FASTFORWARD, SIMULATION, ButtonsTexture, ButtonSize, Position, scale);
        ButtonVector.push_back(pAddMe);
        // add HEATMAP Button
         Position.x+=ButtonSize.x*1.5*scale;
        id++;
        pAddMe = new ClSimpleButton(id, HEATMAP, SIMULATION, ButtonsTexture, ButtonSize, Position, scale);
        ButtonVector.push_back(pAddMe);
        // add BOMB Button
        // add FIRE Button
    }
    void ClSimpleGUI::Execute(Buttons btn)
    {
        switch(btn)
        {
        case(HEATMAP):
            {
                ClHeatMap::toggleDraw();
            }
            // add more functionality
        }
    }  // called to execute code when a button is pressed

