#ifndef FLEESTATE_HPP
#define FLEESTATE_HPP

#include "AbstractState.hpp"

class ClLeavingState : public ClAbstractState
{
    public:
    ClLeavingState(int id, ClStateMachine *pStateMachine)
    {
        this->id = id;
        this->pStateMachine = pStateMachine;
    }
    enum STATES update() const;

};

#endif // FLEESTATE_HPP
