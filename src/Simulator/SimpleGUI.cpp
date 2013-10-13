#include "../../include/Simulator/SimpleGUI.hpp"

   ClSimpleGUI::ClSimpleGUI(const sf::Vector2f &ScreenSize)
    {
        id = 0;
        this->ScreenSize = ScreenSize;
        ButtonsTexture.loadFromFile("pictures/ButtonSet1.png");
        labelFont.loadFromFile("fonts/LiberationSerif-Regular.ttf");

        CreateAllButtons();
        CreateAllLabels();
    }

    ClSimpleGUI::~ClSimpleGUI()
    {
        for(unsigned int n = 0; n< ButtonVector.size();n++)
        {
            delete ButtonVector[n];
        }

        for(unsigned int n = 0; n< LabelVector.size();n++)
        {
            delete LabelVector[n];
        }

    }

    void ClSimpleGUI::draw(sf::RenderWindow &window)
    {

        for(unsigned int n = 0; n< ButtonVector.size();n++)
        {
            ButtonVector[n]->draw(window);
        }

        for(unsigned int n = 0; n< LabelVector.size();n++)
        {
            LabelVector[n]->draw(window);
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

        // Add down right Buttons
        Position.x = ScreenSize.x;
        Position.y = ScreenSize.y;

        Position.y -= ButtonSize.y;
        Position.x -= 0.25 *ButtonSize.x;

        // add HEATMAP Button
         Position.x-=ButtonSize.x*1.5*scale;
        id++;
        pAddMe = new ClSimpleButton(id, HEATMAP, SIMULATION, ButtonsTexture, ButtonSize, Position, scale);
        ButtonVector.push_back(pAddMe);
        // add BOMB Button
        Position.x-=ButtonSize.x*1.5*scale;
        id++;
        pAddMe = new ClSimpleButton(id, BOMB, SIMULATION, ButtonsTexture, ButtonSize, Position, scale);
        ButtonVector.push_back(pAddMe);
        // add FIRE Button
        Position.x-=ButtonSize.x*1.5*scale;
        id++;
        pAddMe = new ClSimpleButton(id, FIRE, SIMULATION, ButtonsTexture, ButtonSize, Position, scale);
        ButtonVector.push_back(pAddMe);
    }

    void ClSimpleGUI::CreateAllLabels()
    {
        ClSimpleLabel *pAddLabel;
        //ClSimpleLabel::ClSimpleLabel(const sf::Vector2f &position, const sf::Vector2f &labelSize, const sf::String &labelText, const sf::Font &font, int *pNumber)
        //add label for counting people (top left)
        sf::Vector2f labelSize(200,100);
        sf::Vector2f position(10,10);
        sf::String labelText("Number of people");

        id++;
        pAddLabel = new ClSimpleLabel(position, labelSize, labelText, labelFont, ClCrowdManager::getPeopleCount());
        LabelVector.push_back(pAddLabel);

    }

    void ClSimpleGUI::Execute(Buttons btn)
    {
        switch(btn)
        {
        case(HEATMAP):
            {
                ClHeatMap::toggleDraw();
            }break;
        case(PLAY):
            {
                ClSimulation::updateSpeed(false, true, false);
            }break;
        case(FASTFORWARD):
            {
                ClSimulation::updateSpeed(false, false, true);
            }break;
        case(PAUSE):
            {
                ClSimulation::updateSpeed(true,false,false);
            }

            // add more functionality
        }

    }  // called to execute code when a button is pressed

