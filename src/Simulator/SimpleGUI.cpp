#include "../../include/Simulator/SimpleGUI.hpp"

ClSimpleGUI::ClSimpleGUI(const sf::Vector2f &ScreenSize)
{

    this->ScreenSize = ScreenSize;
    labelFont.loadFromFile("fonts/LiberationSerif-Regular.ttf");


    createAllMenus();
    pCurrentMenu = MenuVector.front();
    curState = pCurrentMenu->getMyState();
}

ClSimpleGUI::~ClSimpleGUI()
{
    for(unsigned int n = 0; n< MenuVector.size(); n++)
    {
        delete MenuVector[n];
    }
}

void ClSimpleGUI::draw(sf::RenderWindow &window)
{
    pCurrentMenu->draw(window);
}

enum GameStates ClSimpleGUI::update( sf::RenderWindow &window, bool mouseReleased)     // executes code when a button is pressed
{
    enum GameStates testState = pCurrentMenu->update(window, mouseReleased);
    if ( testState != this->curState)
    {
        // time to change the Menu
        curState = testState;
        for ( unsigned int n = 0; n < MenuVector.size(); n++)
        {
            if(MenuVector[n]->getMyState()==curState)
            {
                pCurrentMenu = MenuVector[n];
                break;
            }
        }
    }
    return curState;

}
/*
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
*/

void ClSimpleGUI::createAllMenus()
{
    ClSimpleStartMenu *pStartMenu = new ClSimpleStartMenu(MENU,&labelFont,ScreenSize);
    MenuVector.push_back(pStartMenu);

    ClSimpleSimulationMenu *pSimulationMenu = new ClSimpleSimulationMenu(SIMULATION,&labelFont,ScreenSize);
    MenuVector.push_back(pSimulationMenu);
}
