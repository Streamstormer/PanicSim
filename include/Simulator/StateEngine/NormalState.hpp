#ifndef NORMALSTATE_HPP
#define NORMALSTATE_HPP

#include "AbstractState.hpp"

class ClNormalState : public ClAbstractState
{
    public:
    ClNormalState(int id, enum STATES myState)
    {
        this->myState = myState;
        this->id = id;
    }
    enum STATES update(bool panic) const;
    // what action next
    virtual enum ACTIONS getNextAction() const ;

};

#endif // NORMALSTATE_HPP
