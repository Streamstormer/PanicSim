#ifndef ABSTRACTSTATE_HPP
#define ABSTRACTSTATE_HPP


enum STATES{NORMAL,PANIC,CONFUSED,LEAVING};
enum ACTIONS{LEAVETOEXIT, PANICHARD, NOTHING};

class ClAbstractState
{
public:
    ClAbstractState() {}
    virtual ~ClAbstractState() {}
    // use StateMachine to determine what to do next
    virtual enum STATES update(bool panic) = 0;
    // what action next
    virtual enum ACTIONS getNextAction() const = 0;
    int getID() {return id;}
    enum STATES getState() {return myState;};
protected:
    static bool panicState; // true if at least one crowd has been in panic state
    int id;
    enum STATES myState;
};
#endif // ABSTRACTSTATE_HPP
