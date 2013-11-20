//Please look for the description in the header file


#include "../../include/Simulator/CrowdPartition.hpp"

ClCrowdPartition::ClCrowdPartition()
{
    //ctor
}

ClCrowdPartition::~ClCrowdPartition()
{
    //dtor
}

void ClCrowdPartition::partitionCrowds(int totalVisitors, ClArea *pArea, ClCrowdManager *pCrowdManager)
{
    this->pArea = pArea;
    ClFastSquareroot fSR;
    int sum = 0;
    int counter = pArea->getNumberOfStaticObjects();
    int priority[counter];
    calculatePriorities(&sum, priority, counter);
    double persons;
    sf::Vector2f sPosition;
    sf::Vector2f sVector;
    sf::Vector2f sUnitVector;
    sf::Vector2f vCrowdCandidate;
    sf::Vector2f vCandidateWa;
    double vectorDistance;

    int attractionLength;
    int numOfCrowds;
    int personsPerCrowd;

    ClStaticObject *pObject;
    ClPathFinder *pPF = new ClPathFinder(pArea, PATH_TEST_GRANULARITY, pArea->getLevelSize());
    ClPath *pPath = NULL;


    const int vMaxX = pArea->getLevelSize().x - 5;
    const int vMaxY = pArea->getLevelSize().y - 5;


    for(int i = 0; i < counter; i++)
    {
        if(priority[i])
        {
            persons = (priority[i] * totalVisitors / sum);
            pObject = pArea->getObject(i+1);

            sPosition = pObject->getCenter();
            sVector = sf::Vector2f(2.0 * (pObject->getMiddleOfLine().x - sPosition.x), 1.5 * (pObject->getMiddleOfLine().y - sPosition.y));
            vectorDistance = fSR.getSqrt(std::pow(sVector.x,2) + std::pow(sVector.y,2));
            if(vectorDistance != 0)
            {
                sUnitVector.x = sVector.x / vectorDistance;
                sUnitVector.y = sVector.y / vectorDistance;
            }
            else
            {
                std::cout << "Division by zero when calculating the Unit vector.";
            }
            //std::cout << "persons before: " << persons;
            /*******IF THIS IS THE LAST PLACEMENT OF A CROWD, THE INACCURACY FOR TOTAL VISITORS IS CORRECTED*********/
            if(! pArea->attractionWithHigherId(i+2))
            {
                persons += (double) (totalVisitors - *(pCrowdManager->getPeopleCount()) - persons);
            }

            // pObject->getSize().x is always the attraction length
            attractionLength = pObject->getSize().x;


            numOfCrowds = attractionLength / DIST_CROWDS_PER_ATTR;
            if(!numOfCrowds)
            {
                numOfCrowds = 1;
            }

            /*****Calculation candidate for Crowd positioning*****/

            personsPerCrowd = persons / numOfCrowds;
            vCrowdCandidate.x = sPosition.x + sVector.x + (fSR.getSqrt(persons) * 2 * sUnitVector.x + 10);
            vCrowdCandidate.y = sPosition.y + sVector.y + (fSR.getSqrt(persons) * 2 * sUnitVector.y + 10);
            if(abs(sUnitVector.x) < abs(sUnitVector.y))
            {
                if(numOfCrowds > 1)
                {
                    vCrowdCandidate.x -= numOfCrowds * DIST_CROWDS_PER_ATTR / 2 - DIST_CROWDS_PER_ATTR / 2;
                }
            }else
            {
                if(numOfCrowds > 1)
                {
                    vCrowdCandidate.y -= numOfCrowds * DIST_CROWDS_PER_ATTR / 2 - DIST_CROWDS_PER_ATTR / 2;
                }
            }


            for(int j = 0; j < numOfCrowds; j++)
            {
                if(pPath != NULL)
                {
                    delete pPath;
                }
                pPath = pPF->findPath(vCrowdCandidate,
                pArea->getClosestExit(vCrowdCandidate));



                vCandidateWa = vCrowdCandidate;
                while(pPath == NULL)
                {
                    if((vCandidateWa.x + (POS_TRY_GRAN * sUnitVector.x)) > 5
                            && vCandidateWa.x + (POS_TRY_GRAN * sUnitVector.x) < vMaxX
                            && vCandidateWa.y + (POS_TRY_GRAN * sUnitVector.y) > 5
                            && vCandidateWa.y + (POS_TRY_GRAN * sUnitVector.y) < vMaxY)
                    {
                        vCandidateWa.x += POS_TRY_GRAN * sUnitVector.x;
                        vCandidateWa.y += POS_TRY_GRAN * sUnitVector.y;
                        delete pPath;
                        pPath = pPF->findPath(sf::Vector2f(sPosition.x + sVector.x, sPosition.y + sVector.y), pArea->getClosestExit(sf::Vector2f(sPosition.x + sVector.x, sPosition.y + sVector.y)));
                    }
                    else
                    {
                        std::cout << "Not able to place crowd with id" << (i + 1);
                    }
                }
                if(j == numOfCrowds - 1)
                    personsPerCrowd += (persons - personsPerCrowd * numOfCrowds);
                pCrowdManager->CreateCrowd(vCandidateWa,(int)(fSR.getSqrt(personsPerCrowd) * 5 + 20), personsPerCrowd);
                if(abs(sUnitVector.x) < abs(sUnitVector.y))
                {
                    vCrowdCandidate.x += DIST_CROWDS_PER_ATTR;
                }else
                {
                    vCrowdCandidate.y += DIST_CROWDS_PER_ATTR;
                }
            }
        }
    }
    delete pPath;
    delete pPF;
}

void ClCrowdPartition::calculatePriorities(int *sum, int *priority, int counter)
{
    sf::Vector2f sSize;
    enum staticObjects sType;
    for(int i = 0; i < counter; i++)
    {
        priority[i] = 0;
        sType = pArea->getType(i+1);
        sSize = pArea->getSize(i+1);
        switch(sType)
        {
        case STAGE:
            priority[i] = 3;
            break;
        case BAR:
            priority[i] = 2;
            break;
        case WC:
            priority[i] = 5;
            break;
        default:
            priority[i] = 0;
        }

        priority[i] = priority[i] * sSize.x * sSize.y / 1000;
        *sum += priority[i];
    }

}
