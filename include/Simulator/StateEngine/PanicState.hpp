#ifndef PANICSTATE_HPP
#define PANICSTATE_HPP

#include <SFML/Graphics.hpp>
#include "AbstractState.hpp"


class ClPanicState : public ClAbstractState
{
    public:
    ClPanicState(int id, ClStateMachine *pStateMachine, enum STATES myState)
    {
        panicClock.restart();
        this->myState = myState;
        this->id = id;
        this->pStateMachine = pStateMachine;
    }
    enum STATES update(bool panic) const;
    // what action next
    virtual enum ACTIONS getNextAction() const ;
    private:
        static const int panicTime = 5; // Panic Time in Seconds
        sf::Clock panicClock;
};

#endif // PANICSTATE_HPP
