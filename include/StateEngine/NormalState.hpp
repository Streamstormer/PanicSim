#ifndef NORMALSTATE_HPP
#define NORMALSTATE_HPP

#include "AbstractState.hpp"

class ClNormalState : public ClAbstractState
{
    public:
    ClNormalState(int id, ClStateMachine *pStateMachine)
    {
        this->id = id;
        this->pStateMachine = pStateMachine;
    }
    enum STATES update() const;

};

#endif // NORMALSTATE_HPP
