
#include "../../include/Simulator/SimpleSimulationMenu.hpp"


ClSimpleSimulationMenu::ClSimpleSimulationMenu(enum GameStates myState, sf::Font *pFont, sf::Vector2f screenSize)
{
    this->myState = myState;
    this->pFont = pFont;
    this->screenSize = screenSize;
    texture.loadFromFile("pictures/ButtonSet1.png");
    texture2.loadFromFile("pictures/ButtonSet3.png");
    texture3.loadFromFile("pictures/Button.png");
    createMenu();
}

void ClSimpleSimulationMenu::draw(sf::RenderWindow &window) const
{
    for(int n = 0; n < ButtonVector.size(); n++)
    {
        ButtonVector[n]->draw(window);
    }
    for(int n =0; n< LabelVector.size(); n++)
    {
        LabelVector[n]->draw(window);
    }
}

enum GameStates ClSimpleSimulationMenu::execute(enum Buttons btn) const
{
    switch(btn)
    {
    case(HEATMAP):
        {
            ClHeatMap::toggleDraw();
            ClStatistic::setAverageDraw(false);
            ClSimulation::setStopSim(false);
        }
        break;
    case(PLAY):
    {
        ClSimulation::updateSpeed(false, true, false);
        ClStatistic::setAverageDraw(false);
        ClSimulation::setStopSim(false);
    }
    break;
    case(FASTFORWARD):
    {
        ClSimulation::updateSpeed(false, false, true);
        ClStatistic::setAverageDraw(false);
        ClSimulation::setStopSim(false);
    }
    break;
    case(PAUSE):
    {
        ClSimulation::updateSpeed(true,false,false);
        ClStatistic::setAverageDraw(false);
        ClSimulation::setStopSim(false);
    }
    break;
    case(BOMB):
    {
        ClThreatManager::buttonPressed(true, false, false);
        ClStatistic::setAverageDraw(false);
        ClSimulation::setStopSim(false);
    }
    break;
    case(FIRE):
    {
        ClThreatManager::buttonPressed(false, true, false);
        ClStatistic::setAverageDraw(false);
        ClSimulation::setStopSim(false);
    }
    break;
    case(EXPLOSION):
    {
        ClThreatManager::buttonPressed(false,false,true);
        ClStatistic::setAverageDraw(false);
        ClSimulation::setStopSim(false);
    }
    break;
    case(STATISTIC):
    {
        ClStatistic::setAverageDraw(true);
        ClSimulation::setStopSim(false);
        ClStatistic::rememberTime();
    }
    break;
    case(EXITMENU):
    {
        ClStatistic::setAverageDraw(false);
        ClSimulation::setStopSim(true);
    }
    break;
    }
    return SIMULATION;
}

//virtual void execute(enum Buttons btn) const = 0;
enum GameStates ClSimpleSimulationMenu::update(sf::RenderWindow &window, bool mouseReleased) const
{
    for (unsigned int n = 0; n<ButtonVector.size(); n++)
    {
        if (ButtonVector[n]->isPressed(window))
        {
            if(mouseReleased == true)
            {
                execute(ButtonVector[n]->getButtonType());
                if(ClStatistic::getAverageDraw()==true) return STATISTICS;
                if(ClSimulation::getStopSim()==true) return MENU;
            }
        }
    }
    return SIMULATION;
}
// private:
void ClSimpleSimulationMenu::createMenu()
{
    ClSimpleButton *pAddMe;
    int id = 0;
    sf::Vector2f ButtonSize;
    ButtonSize.x = texture.getSize().x;
    ButtonSize.y = texture.getSize().y;
    ButtonSize.x /=2;
    ButtonSize.y /=3;
    sf::Vector2f Position;
    Position.x = ButtonSize.x / 2;
    Position.y = this->screenSize.y - ButtonSize.y;
    float scale = 0.35f;
    // add STOP Button
    id++;
    pAddMe = new ClSimpleButton(id, STOP,2, texture, ButtonSize, Position, scale);
    ButtonVector.push_back(pAddMe);
    // add PLAY Button
    Position.x+=ButtonSize.x*1.5*scale;
    id++;
    pAddMe = new ClSimpleButton(id, PLAY,3, texture, ButtonSize, Position, scale);
    ButtonVector.push_back(pAddMe);
    // add FASTFORWARD Button
    Position.x+=ButtonSize.x*1.5*scale;
    id++;
    pAddMe = new ClSimpleButton(id, FASTFORWARD,4, texture, ButtonSize, Position, scale);
    ButtonVector.push_back(pAddMe);

    // Add down right Buttons
    Position.x = screenSize.x;
    Position.y = screenSize.y;

    Position.y -= ButtonSize.y;
    Position.x -= 0.25 *ButtonSize.x;

    // add HEATMAP Button
    Position.x-=ButtonSize.x*1.5*scale;
    id++;
    pAddMe = new ClSimpleButton(id, HEATMAP,0, texture, ButtonSize, Position, scale);
    ButtonVector.push_back(pAddMe);
    // add BOMB Button
    Position.x-=ButtonSize.x*1.5*scale;
    id++;
    pAddMe = new ClSimpleButton(id, BOMB,1, texture, ButtonSize, Position, scale);
    ButtonVector.push_back(pAddMe);
    // add FIRE Button
    Position.x-=ButtonSize.x*1.5*scale;
    id++;
    pAddMe = new ClSimpleButton(id, FIRE,5, texture, ButtonSize, Position, scale);
    ButtonVector.push_back(pAddMe);
    // add EXPLOSION Button
    Position.x-=ButtonSize.x*1.5*scale;
    id++;
    pAddMe = new ClSimpleButton(id, EXPLOSION,0, texture2, ButtonSize, Position, scale);
    ButtonVector.push_back(pAddMe);
    // add STATISTIC Button
    id++;
    ButtonSize.x = (float)texture3.getSize().x;
    ButtonSize.y = (float)texture3.getSize().y;
    Position.x = 9*screenSize.x/10-ButtonSize.x/2;
    Position.y = screenSize.y/8;
    pAddMe = new ClSimpleButton(id, STATISTIC, 0, texture3, ButtonSize, Position, 0.8f);
    pAddMe->setText(sf::String("Statistic"), pFont);
    ButtonVector.push_back(pAddMe);
    // add MENU Button (exit to menu)
    id++;
    Position.y += 3*ButtonSize.y/2;
    pAddMe = new ClSimpleButton(id, EXITMENU, 0, texture3, ButtonSize, Position, 0.8f);
    pAddMe->setText(sf::String("MENU"),pFont);
    ButtonVector.push_back(pAddMe);

    // Labels
    ClSimpleLabel*pLabel;
    Position.x=Position.y=0;
    pLabel= new ClSimpleLabel(Position, sf::Vector2f(200,100), sf::String("Besucher"),*pFont,ClCrowdManager::getPeopleCount());
    LabelVector.push_back(pLabel);
}
