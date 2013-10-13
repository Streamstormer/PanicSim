#include <SFML/Graphics.hpp>
#ifndef SIMPLE_GUI_INCLUDE
#define SIMPLE_GUI_INCLUDE

#include <vector>
#include "SimpleButton.hpp"
#include "SimpleLabel.hpp"
#include "HeatMap.hpp"
#include "CrowdManager.hpp"
#include "Simulation.hpp"

enum GameStates {MENU, SIMULATION, PAUSE};

class ClSimpleGUI
{
public:
    ClSimpleGUI(const sf::Vector2f &ScreenSize);
    ~ClSimpleGUI();

    void draw(sf::RenderWindow &window);
    void update( sf::RenderWindow &window);     // executes code when a button is pressed

private:

    void CreateAllButtons();// called in the constructor to create all buttons
    void CreateAllLabels();// called in the constructor to create all labels
    void Execute(Buttons btn);

    std::vector<ClSimpleButton *> ButtonVector;
    std::vector<ClSimpleLabel *> LabelVector;
    sf::Texture ButtonsTexture;
    sf::Font labelFont;
    int id;                     // used to give Buttons a unique id
    sf::Vector2f ScreenSize;
};

#endif // SIMPLE_GUI_INCLUDE
