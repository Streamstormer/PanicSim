#ifndef STATEVAULT_HPP
#define STATEVAULT_HPP

#include <vector>
#include <iostream>

// include all the different states here
#include "NormalState.hpp"
#include "LeavingState.hpp"
#include "PanicState.hpp"

class ClStateVault
{
public:
    ClStateVault();
    //Cleanup remaining states
    ~ClStateVault();

    ClAbstractState* requestStartState();
    ClAbstractState* requestNewState(enum STATES newState, int oldId);

private:
    ClAbstractState* createState(enum STATES state);
    std::vector<ClAbstractState *> StatesVector;
    int id;
};

#endif // STATEVAULT_HPP
