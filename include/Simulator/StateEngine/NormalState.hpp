#ifndef NORMALSTATE_HPP
#define NORMALSTATE_HPP

#include "AbstractState.hpp"

class ClNormalState : public ClAbstractState
{
    public:
    ClNormalState(int id, ClStateMachine *pStateMachine, enum STATES myState)
    {
        this->myState = myState;
        this->id = id;
        this->pStateMachine = pStateMachine;
    }
    enum STATES update() const;
    // what action next
    virtual enum ACTIONS getNextAction() const ;

};

#endif // NORMALSTATE_HPP
