#ifndef STATEVAULT_HPP
#define STATEVAULT_HPP

#include <vector>


// include all the different states here
#include "NormalState.hpp"
#include "LeavingState.hpp"
#include "PanicState.hpp"

class ClStateVault
{
public:
    ClStateVault() {id = 0;}
    //Cleanup remaining states
    ~ClStateVault()
    {
        for ( unsigned int n = 0; n < StatesVector.size();n++)
        {
            delete StatesVector[n];
        }
    }
    ClAbstractState* requestStartState() {return createState(NORMAL);}
    ClAbstractState* requestNewState(enum STATES newState, int oldId)
    {
        unsigned int n = 0;
        while ( n < StatesVector.size() && (StatesVector[n]->getID() != oldId) )
        {
            n++;
        }

        if ((StatesVector[n]->getID() != oldId))
        {
            delete StatesVector[n];
            StatesVector.erase(StatesVector.begin()+n);
        }
        // else oldID is invalid

        return createState(newState);
    }
private:
    ClAbstractState* createState(enum STATES state)
    {
        switch (state)
        {
        case (NORMAL):
            {
                ClNormalState *pAddMe = new ClNormalState(id,&StateMachine,NORMAL);
                StatesVector.push_back(pAddMe);
                return pAddMe;
            }
        case (LEAVING):
            {
                ClLeavingState *pAddMe = new ClLeavingState(id,&StateMachine,LEAVING);
                StatesVector.push_back(pAddMe);
                return pAddMe;
            }
        case (PANIC):
            {
                ClPanicState *pAddMe = new ClPanicState(id,&StateMachine,PANIC);
                StatesVector.push_back(pAddMe);
                return pAddMe;
            }
        }
    }
    std::vector<ClAbstractState *> StatesVector;
    ClStateMachine StateMachine;
    int id;
};

#endif // STATEVAULT_HPP
