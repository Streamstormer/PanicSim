#include "../../../include/Simulator/StateEngine/AbstractState.hpp"

bool ClAbstractState::panicState = false;

void ClAbstractState::clearPanicState()
{
    panicState = false;
}
