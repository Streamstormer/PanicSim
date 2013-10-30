#include "../../../include/Simulator/StateEngine/NormalState.hpp"
enum STATES ClNormalState::update() const
{
    if(pStateMachine->isInDangerByThreat() || pStateMachine->isHearThreat())
    {
        return LEAVING;
    }
    return NORMAL;
}

enum ACTIONS ClNormalState::getNextAction() const
{
    // do nothing just stand there
    return NOTHING;
}
