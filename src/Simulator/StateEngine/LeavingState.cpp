#include "../../../include/Simulator/StateEngine/LeavingState.hpp"
enum STATES ClLeavingState::update(bool panic) const
{
    return LEAVING;
}

enum ACTIONS ClLeavingState::getNextAction() const
{
    return LEAVETOEXIT;
}
