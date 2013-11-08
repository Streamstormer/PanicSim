#ifndef ABSTRACTSTATE_HPP
#define ABSTRACTSTATE_HPP

#include "StateMachine.hpp"

enum STATES{NORMAL,PANIC,CONFUSED,LEAVING};
enum ACTIONS{LEAVETOEXIT, PANICHARD, NOTHING};

class ClAbstractState
{
public:
    ClAbstractState() {}
    virtual ~ClAbstractState() {}
    // use StateMachine to determine what to do next
    virtual enum STATES update(bool panic) const = 0;
    // what action next
    virtual enum ACTIONS getNextAction() const = 0;
    int getID() {return id;}
    enum STATES getState() {return myState;};
protected:
    int id;
    enum STATES myState;
    ClStateMachine *pStateMachine;
};

#endif // ABSTRACTSTATE_HPP
