#ifndef FLEESTATE_HPP
#define FLEESTATE_HPP

#include "AbstractState.hpp"

class ClLeavingState : public ClAbstractState
{
    public:
    ClLeavingState(int id, ClStateMachine *pStateMachine, enum STATES myState)
    {
        this->myState = myState;
        this->id = id;
        this->pStateMachine = pStateMachine;
    }
    enum STATES update() const;

    // what action next ?
    enum ACTIONS getNextAction() const ;


};

#endif // FLEESTATE_HPP
