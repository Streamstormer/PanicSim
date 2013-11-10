
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
    for(unsigned int n = 0; n < ButtonVector.size(); n++)
    {
        ButtonVector[n]->draw(window);
    }
    for(unsigned int n =0; n< LabelVector.size(); n++)
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
        }
        break;
    case(PLAY):
    {
        ClSimulation::updateSpeed(false, true, false);
    }
    break;
    case(FASTFORWARD):
    {
        ClSimulation::updateSpeed(false, false, true);
    }
    break;
    case(PAUSE):
    {
        ClSimulation::updateSpeed(true,false,false);
    }
    break;
    case(BOMB):
    {
        ClThreatManager::buttonPressed(true, false, false);
    }
    break;
    case(FIRE):
    {
        ClThreatManager::buttonPressed(false, true, false);
    }
    break;
    case(EXPLOSION):
    {
        ClThreatManager::buttonPressed(false,false,true);
    }
    break;
    case(STATISTIC):
    {
        ClStatistic::setDoDrawStatistic(true);
        ClStatistic::setInStatistic(true);
        return STATISTICS;
    }
    break;
    case(EXITMENU):
    {
        return MENU;
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
                return execute(ButtonVector[n]->getButtonType());
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
    ButtonSize.y /=4;
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
    scale = 0.5;
    ButtonSize.x = texture.getSize().x;
    ButtonSize.y = texture.getSize().y;
    ButtonSize.x /=2;
    ButtonSize.y /=4;
    Position.x = screenSize.x-2*1.5*ButtonSize.x*scale;
    Position.y = 0;
    pAddMe = new ClSimpleButton(id, STATISTIC, 6, texture, ButtonSize, Position, scale);
    ButtonVector.push_back(pAddMe);
    // add MENU Button (exit to menu)
    id++;
    Position.x += ButtonSize.x*1.5*scale;
    pAddMe = new ClSimpleButton(id, EXITMENU, 7, texture, ButtonSize, Position, scale);
    ButtonVector.push_back(pAddMe);

    // Labels
    ClSimpleLabel*pLabel;
    Position.x=Position.y=0;
    sf::Vector2f labelSize(200,100);
    pLabel= new ClSimpleLabel(Position, labelSize, sf::String("Besucher"),*pFont,ClCrowdManager::getPeopleCount());
    LabelVector.push_back(pLabel);

    Position.x += labelSize.x;
    pLabel = new ClSimpleLabel(Position, labelSize, sf::String("Tote"), *pFont, ClStatistic::getNumberCasualties());
    LabelVector.push_back(pLabel);

    Position.x = ButtonSize.x / 2;
    Position.y = this->screenSize.y - ButtonSize.y;
    Position.x += 2*ButtonSize.x*1.5*scale;
    labelSize.x = 130;
    labelSize.y = 80;

    pLabel = new ClSimpleLabel(Position, labelSize, sf::String("Speed"), *pFont, ClStatistic::getSpeed());
    LabelVector.push_back(pLabel);
}
