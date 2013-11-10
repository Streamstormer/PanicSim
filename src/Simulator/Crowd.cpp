#include "../../include/Simulator/Crowd.hpp"

ClCrowd::ClCrowd(float radius, ClArea * pArea, sf::Color Color, sf::Vector2f position, int numOfPeoples, ClHeatMap *pHeatMap, ClStateVault *pStateVault, ClPathFinder *pPathfinder)
{
    // no casualties yet
    panic = false;

    this->position = position;
    this->Color = Color;
    positionMid.x = positionMid.y = 0;

    this->radius = radius;
    this->pArea = pArea;
    this->pHeatMap = pHeatMap;
    this->pPathFinder = pPathfinder;
    pPath = NULL;

    //randomize the position of the people
    for (int n = 0; n < numOfPeoples; n++)
    {
        StrPeople *newPerson = new StrPeople;
        newPerson->alive = true;
        newPerson->panic = false;
        newPerson->currentNode = -1;
        newPerson->force.x = newPerson->force.y = 0;

        do
        {
            newPerson->position[PEOPLE_POSITION_MEMORY-1].x = std::rand();
            newPerson->position[PEOPLE_POSITION_MEMORY-1].x = (int)newPerson->position[PEOPLE_POSITION_MEMORY-1].x % (int)(2*radius);
            newPerson->position[PEOPLE_POSITION_MEMORY-1].x -= radius;

        } while (newPerson->position[(PEOPLE_POSITION_MEMORY - 1)].x < 0);

        do
        {
            newPerson->position[PEOPLE_POSITION_MEMORY-1].y = std::rand();
            newPerson->position[PEOPLE_POSITION_MEMORY-1].y = (int)newPerson->position[PEOPLE_POSITION_MEMORY-1].y % (int)(2*radius);
            newPerson->position[PEOPLE_POSITION_MEMORY-1].y -= radius;

        } while (newPerson->position[(PEOPLE_POSITION_MEMORY - 1)].y < 0);

        //Add Offset
        newPerson->position[PEOPLE_POSITION_MEMORY - 1].x += position.x - radius / 2 ;
        newPerson->position[PEOPLE_POSITION_MEMORY - 1].y += position.y - radius / 2;

        //Copy for history
        for(int i = 0; i < (PEOPLE_POSITION_MEMORY - 1); i++)
        {
            newPerson->position[i] = newPerson->position[PEOPLE_POSITION_MEMORY-1];
        }
        //positionMemory[] is set to the last position
        for (int j = 0; j < COLLISION_POSITION_MEMORY; j++)
        {
            newPerson->positonMemory[j] = newPerson->position[PEOPLE_POSITION_MEMORY-1];
        }
        peoples.push_back(newPerson);
    }

    // register people in the HeatMap
    pHeatMap->registerCrowd(peoples);

    // get start state
    this->pStateVault = pStateVault;
    pCurrentState = pStateVault->requestStartState();
    curAction = pCurrentState->getNextAction();

    nextNode.x = nextNode.y = -1;
}

ClCrowd::~ClCrowd()
{
    for (unsigned int n = 0; n < peoples.size(); n++)
    {
        delete peoples[n];
    }
    if(pPath != NULL)
    {
        delete pPath;
    }
}

void  ClCrowd::Update(float frameTime)
{
    bool casualtiesOccured = false;
    int casualtieCounter = 0;
    bool firstPanic = !panic;
    // check casualties
    for(unsigned int n = 0; n<peoples.size();n++)
    {
        if (peoples[n]->alive == false )
        {
            if(peoples[n]->panic == true)
            {
                casualtiesOccured = true;
                panic = true;
                if (firstPanic)
                {
                    positionMid.x += peoples[n]->position[PEOPLE_POSITION_MEMORY-1].x;
                    positionMid.y += peoples[n]->position[PEOPLE_POSITION_MEMORY-1].y;
                    panic = true;
                    casualtieCounter++;
                    for(unsigned int m = 0; m<peoples.size(); m++)
                    {
                        peoples[m]->panic = true;
                    }
                }
            }
            delete peoples[n]; // free memory
            peoples.erase(peoples.begin()+n);
        }
    }

    if (casualtiesOccured == true && firstPanic == true)
    {
        positionMid.x /= casualtieCounter;
        positionMid.y /= casualtieCounter;
    }

    if (panic == false)
    {
        // check for nearby panic masses
        for(unsigned int n = 0; n<peoples.size();n++)
        {
            if (peoples[n]->panic == true && peoples[n]->alive == true)
            {
                positionMid.x = -1;
                positionMid.y = -1;
                if (panic == false)
                for(unsigned int m = 0; m<peoples.size(); m++)
                {
                    peoples[m]->panic = true;
                }
                this->panic = true;

            }
        }
    }

    sf::Vector2f force;
     for (unsigned int n = 0; n < peoples.size(); n++)
    {
        for(int i = 0; i < PEOPLE_POSITION_MEMORY - 1; i++)
        {
            peoples[n]->position[i] = peoples[n]->position[i + 1];
        }
    }

    // update state
    enum STATES state =  pCurrentState->update(panic);
    if(state != pCurrentState->getState())
    {
        // change state
        pCurrentState = pStateVault->requestNewState(state,pCurrentState->getID());
        curAction = pCurrentState->getNextAction();
        if(curAction == LEAVETOEXIT)
        {
                //sf::Vector2f exitPosition = pArea->getClosestExit(this->position);
            closestExit = pArea->getClosestExit(this->position);
            std::cerr<<"x,y "<<closestExit.x<<" "<<closestExit.y<<std::endl;
            if (pPath != NULL)
            {
                    delete pPath;
                    pPath = NULL;
            }
            pPath = pPathFinder->findPath(this->position,this->closestExit);
            for (unsigned int n = 0; n < peoples.size(); n++)
            {
                peoples[n]->currentNode = pPath->getFirstNodeId();
            }
        }
    }

    //update logic of crowd
    sf::Vector2f delta;

    switch(curAction)
    {
        case(NOTHING):
        {
            sf::Vector2f force;
            for(unsigned int n = 0; n < peoples.size(); n++)
            {
                // just stand there doing nothing at all
                force =  Seek( peoples[n]->position[(PEOPLE_POSITION_MEMORY - 1)], position);
                //   Vec2DNormalize(&force)
                force.x *= frameTime * -0.01;
                force.y *= frameTime * -0.01;
                peoples[n]->force = force;
            }
        }break;
        case(LEAVETOEXIT):
        {
            sf::Vector2f currentNode;
            for (unsigned int n = 0; n < peoples.size(); n++)
            {
                currentNode = pPath->getNodePosition(peoples[n]->currentNode);
                if( pPath->isLast(peoples[n]->currentNode) == false &&
                   ((peoples[n]->position[(PEOPLE_POSITION_MEMORY - 1)].x - currentNode.x)*
                   (peoples[n]->position[(PEOPLE_POSITION_MEMORY - 1)].x - currentNode.x)
                    +((peoples[n]->position[(PEOPLE_POSITION_MEMORY - 1)].y - currentNode.y)*
                    ((peoples[n]->position[(PEOPLE_POSITION_MEMORY - 1)].y - currentNode.y) )))<90)
                    {

                        peoples[n]->currentNode++;
                    }
                sf::Vector2f force = Seek(peoples[n]->position[(PEOPLE_POSITION_MEMORY - 1)],currentNode);
                force.x *= frameTime * -0.02;
                force.y *= frameTime * -0.02;
                peoples[n]->force = force;
            }
        }break;
        case PANICHARD:
        {
            if (positionMid.x != -1 &&positionMid.y != -1)
            delta =  Seek( sf::Vector2f(positionMid.x,positionMid.y), position);
            else
            {
                delta.x = delta.y = 0;
            }
            Vec2DNormalize(&delta);
            delta.x*=-0.3;
            delta.y*=-0.3;
            // check new position
            if(pArea->validPoint(position+delta))
            {
                position+=delta ;
            }
            sf::Vector2f force;
            for(unsigned int n = 0; n < peoples.size(); n++)
            {
                force =  Seek( peoples[n]->position[(PEOPLE_POSITION_MEMORY - 1)], position);
                if (positionMid.x != -1 && positionMid.y != -1)
                {
                    force.x *= frameTime * -0.1;
                    force.y *= frameTime * -0.1;
                    peoples[n]->force = force;
                }
                else
                {
                    force.x *= frameTime * -0.005;
                    force.y *= frameTime * -0.005;
                    peoples[n]->force = force;
                }
            }
        }
    }
}
void  ClCrowd::Update(sf::Vector2i position,float frameTime)
{
    this->Update(frameTime);
    this->position.x = position.x;
    this->position.y = position.y;
}
void  ClCrowd::Draw(sf::RenderWindow& window)
{
    sf::CircleShape personShape;

    personShape.setFillColor(Color);
    personShape.setRadius(5);
    personShape.setOrigin(2.5,2.5);

    sf::Vector2f avgPosition;

    for(unsigned int n = 0; n< peoples.size(); n++)
    {
        avgPosition.x = 0;
        avgPosition.y = 0;
        for(int i = 0; i < PEOPLE_POSITION_MEMORY; i++)
        {
            avgPosition.x += peoples[n]->position[i].x;
            avgPosition.y += peoples[n]->position[i].y;
        }
        avgPosition.x /= PEOPLE_POSITION_MEMORY;
        avgPosition.y /= PEOPLE_POSITION_MEMORY;
        personShape.setPosition(avgPosition);
        window.draw(personShape);
    }

    // debugging information
    personShape.setPosition(position);
    personShape.setFillColor(sf::Color::Red);
    personShape.setRadius(5);
    personShape.move(sf::Vector2f(-2.5,-2.5));
    window.draw(personShape);

 /*   if (pPath != NULL)
    {
        pPath->drawPath(window);
    }
*/

    if (panic)
    {
        personShape.setPosition(sf::Vector2f(positionMid.x,positionMid.y));
        personShape.setFillColor(sf::Color::Magenta);
        window.draw(personShape);
    }
}

float ClCrowd::getRadius()
{
    return radius;
}

void ClCrowd::Vec2DNormalize( sf::Vector2f *NormalizeMe )
{
    if (NormalizeMe->x != 0 && NormalizeMe->y != 0)
    {

    float helpVar = fabs(NormalizeMe->x) + fabs(NormalizeMe->y);
    NormalizeMe->x /= helpVar;
    NormalizeMe->y /= helpVar;
    }
}

sf::Vector2f ClCrowd::Seek(sf::Vector2f TargetPos, const sf::Vector2f & Destination)
{
    TargetPos.x -= Destination.x;
    TargetPos.y -= Destination.y;

    Vec2DNormalize(&TargetPos);

    return (TargetPos );
}
