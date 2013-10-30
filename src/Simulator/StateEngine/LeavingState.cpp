#include "../../../include/Simulator/StateEngine/LeavingState.hpp"
enum STATES ClLeavingState::update() const
{
    return LEAVING;
}

enum ACTIONS ClLeavingState::getNextAction() const
{
    return LEAVETOEXIT;
}
