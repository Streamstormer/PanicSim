#include <SFML/Graphics.hpp>
#ifndef SIMPLE_GUI_INCLUDE
#define SIMPLE_GUI_INCLUDE

#include <vector>
#include "SimpleButton.hpp"
#include "HeatMap.hpp"

enum GameStates {MENU, SIMULATION, PAUSE};

class ClSimpleGUI
{
public:
    ClSimpleGUI(const sf::Vector2f &ScreenSize)
    {
        id = 0;
        this->ScreenSize = ScreenSize;
        ButtonsTexture.loadFromFile("pictures/ButtonSet1.png");
        CreateAllButtons();
    }
    ~ClSimpleGUI()
    {
        for(unsigned int n = 0; n< ButtonVector.size();n++)
        {
            delete ButtonVector[n];
        }
    }

    void draw(sf::RenderWindow &window)
    {

        for(unsigned int n = 0; n< ButtonVector.size();n++)
        {
            ButtonVector[n]->draw(window);
        }
    }

    void update( sf::RenderWindow &window)     // executes code when a button is pressed
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

private:

    void CreateAllButtons()// called in the constructor to create all buttons
    {
        // add Simulation Buttons
        // add downleft Buttons
        sf::Vector2f ButtonSize(160,160);
        sf::Vector2f Position(0,ScreenSize.y);

        ClSimpleButton *pAddMe;
        float scale = 0.25;

        Position.y-=ButtonSize.x*1,5;
        Position.x += ButtonSize.x*0.5;

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
    void Execute(Buttons btn)
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


    std::vector<ClSimpleButton *> ButtonVector;
    sf::Texture ButtonsTexture;
    int id;                     // used to give Buttons a unique id
    sf::Vector2f ScreenSize;


};

#endif // SIMPLE_GUI_INCLUDE
