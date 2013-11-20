/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Manuel Stampp
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    Analyses the Area and positions Crowds in front of attractions
---------------------------------------------------------------------------------------------------------------------------------------
*/

#ifndef CROWDPARTITION_H
#define CROWDPARTITION_H

#include "Area.hpp"
#include "CrowdManager.hpp"


class ClCrowdPartition
{
    public:
        ClCrowdPartition();
        virtual ~ClCrowdPartition();
        void partitionCrowds(int totalVisitors, ClArea *pArea, ClCrowdManager *pCrowdManager);
    protected:
    private:
        void calculatePriorities(int *sum, int *priority, int counter);



        static const int PATH_TEST_GRANULARITY = 20;
        static const int DIST_CROWDS_PER_ATTR = 120;
        static const int POS_TRY_GRAN = 30;

        ClArea *pArea;
};

#endif // CROWDPARTITION_H
