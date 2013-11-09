#ifndef NORMALSTATE_HPP
#define NORMALSTATE_HPP

#include "AbstractState.hpp"
#include <SFML/System.hpp>

class ClNormalState : public ClAbstractState
{
    public:
    ClNormalState(int id, enum STATES myState)
    {
        this->myState = myState;
        this->id = id;
        waitForLeaving = false;
    }
    enum STATES update(bool panic) ;
    // what action next
    virtual enum ACTIONS getNextAction() const ;
    private:
    static const int LEAVINGTIME = 20;              // Time in seconds between first bomb and all leaving
    bool waitForLeaving;
    sf::Clock panicClock;
};

#endif // NORMALSTATE_HPP
