#include "../../../include/Simulator/StateEngine/NormalState.hpp"
enum STATES ClNormalState::update(bool panic) const
{
    if (panic == true)
    return PANIC;

    return NORMAL;
}

enum ACTIONS ClNormalState::getNextAction() const
{
    return NOTHING;
}
