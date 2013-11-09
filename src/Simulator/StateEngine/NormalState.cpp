#include "../../../include/Simulator/StateEngine/NormalState.hpp"
enum STATES ClNormalState::update(bool panic)
{
    if (panic == true)
    return PANIC;
    if (panicState == true && waitForLeaving == false)
    {
        waitForLeaving = true;
        panicClock.restart();
    }
    if (waitForLeaving && panicClock.getElapsedTime().asSeconds() > LEAVINGTIME)
    return LEAVING;

    return NORMAL;
}

enum ACTIONS ClNormalState::getNextAction() const
{
    return NOTHING;
}
