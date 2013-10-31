#include "../../../include/Simulator/StateEngine/NormalState.hpp"
enum STATES ClNormalState::update() const
{
    return LEAVING;
}

enum ACTIONS ClNormalState::getNextAction() const
{
    return NOTHING;
}
