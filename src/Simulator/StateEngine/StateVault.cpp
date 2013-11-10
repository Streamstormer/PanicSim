#include "../../../include/Simulator/StateEngine/StateVault.hpp"
    ClStateVault::ClStateVault()
    {
        id = 0;
    }
    //Cleanup remaining states
    ClStateVault::~ClStateVault()
    {
        std::cerr<<"stop"<<std::endl;
        for ( unsigned int n = 0; n < StatesVector.size();n++)
        {
            delete StatesVector[n];
        }
        ClAbstractState::clearPanicState();
    }
ClAbstractState* ClStateVault::requestStartState()
    {
        return createState(NORMAL);
    }

ClAbstractState* ClStateVault::requestNewState(enum STATES newState, int oldId)
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

ClAbstractState* ClStateVault::createState(enum STATES state)
    {
        switch (state)
        {
        case (NORMAL):
            {
                ClNormalState *pAddMe = new ClNormalState(id,NORMAL);
                StatesVector.push_back(pAddMe);
                return pAddMe;
            }
        case (LEAVING):
            {
                ClLeavingState *pAddMe = new ClLeavingState(id,LEAVING);
                StatesVector.push_back(pAddMe);
                return pAddMe;
            }
        case (PANIC):
            {
                ClPanicState *pAddMe = new ClPanicState(id,PANIC);
                StatesVector.push_back(pAddMe);
                return pAddMe;
            }break;

        default:
            {
                return NULL;
            }

        }
    }
