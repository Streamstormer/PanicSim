#include "../../../include/Simulator/StateEngine/PanicState.hpp"
enum STATES ClPanicState::update(bool panic)
{
    if (this->panicClock.getElapsedTime().asSeconds()>panicTime)
    return LEAVING;

    return PANIC;
}

enum ACTIONS ClPanicState::getNextAction() const
{
    return PANICHARD;
}
