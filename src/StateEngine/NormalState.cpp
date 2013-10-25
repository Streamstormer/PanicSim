#include "../../include/StateEngine/NormalState.hpp"
enum STATES ClNormalState::update() const
{
    if(pStateMachine->isInDangerByThreat() || pStateMachine->isHearThreat())
    {
        return PANIC;
    }
    return NORMAL;
}
