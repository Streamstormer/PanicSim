#include "../../include/Simulator/SimpleMenu.hpp"

ClSimpleMenu::~ClSimpleMenu()
{
    // free memory
    for (unsigned int n = 0; n < ButtonVector.size();n++)
    {
        delete ButtonVector[n];
    }
    for (unsigned int n = 0; n < LabelVector.size(); n++)
    {
        delete LabelVector[n];
    }
};
enum GameStates ClSimpleMenu::getMyState(){return myState;}
