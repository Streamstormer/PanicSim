#ifndef FLEESTATE_HPP
#define FLEESTATE_HPP

#include "AbstractState.hpp"

class ClLeavingState : public ClAbstractState
{
    public:
    ClLeavingState(int id, enum STATES myState)
    {
        this->myState = myState;
        this->id = id;
    }
    enum STATES update(bool panic) const;

    // what action next ?
    enum ACTIONS getNextAction() const ;


};

#endif // FLEESTATE_HPP
