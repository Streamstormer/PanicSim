#include "../../include/Simulator/Crowd.hpp"


ClCrowd::ClCrowd(float radius, ClArea * pArea, sf::Color Color, sf::Vector2f position, int numOfPeoples, ClHeatMap *pHeatMap, ClStateVault *pStateVault, ClPathFinder *pPathfinder)
{
    this->position = position;
    oldPosition = position;
    this->Color = Color;

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
        newPerson->force.x = newPerson->force.y = 0;
        do
        {
            newPerson->position[PEOPLE_POSITION_MEMORY-1].x = std::rand();
            newPerson->position[PEOPLE_POSITION_MEMORY-1].x = (int)newPerson->position[PEOPLE_POSITION_MEMORY-1].x % (int)(2*radius);
            newPerson->position[PEOPLE_POSITION_MEMORY-1].x -= radius;
            for(int i = 0; i < (PEOPLE_POSITION_MEMORY - 1); i++)
            {
                newPerson->position[i].x = newPerson->position[PEOPLE_POSITION_MEMORY-1].x;
            }
        } while (newPerson->position[(PEOPLE_POSITION_MEMORY - 1)].x < 0);

        do
        {
            newPerson->position[PEOPLE_POSITION_MEMORY-1].y = std::rand();
            newPerson->position[PEOPLE_POSITION_MEMORY-1].y = (int)newPerson->position[PEOPLE_POSITION_MEMORY-1].y % (int)(2*radius);
            newPerson->position[PEOPLE_POSITION_MEMORY-1].y -= radius;
            for(int i = 0; i < (PEOPLE_POSITION_MEMORY - 1); i++)
            {
                newPerson->position[i].y = newPerson->position[PEOPLE_POSITION_MEMORY-1].y;
            }
        } while (newPerson->position[(PEOPLE_POSITION_MEMORY - 1)].y < 0);

        //Add Offset
        for(int i = 0; i < (PEOPLE_POSITION_MEMORY); i++)
        {
            newPerson->position[i].x += position.x ;
            newPerson->position[i].y += position.y;
        }
        //newPerson->forceVec.x = newPerson->forceVec.y =0;
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
    // look for casualties
    for (unsigned int n = 0; n < peoples.size(); n++)
    {
        if (peoples[n]->alive == false)
        {
            delete peoples[n]; // free memory
            peoples.erase(peoples.begin()+n);
        }
    }

    float movementFactor = 1.0f;
    if(position == oldPosition)
    {
        movementFactor = 0.75f;
    }
    sf::Vector2f force;
     for (unsigned int n = 0; n < peoples.size(); n++)
    {
        /*****Center Force****/
        //Succeed
        for(int i = 0; i < PEOPLE_POSITION_MEMORY - 1; i++)
        {
            peoples[n]->position[i] = peoples[n]->position[i + 1];
        }

         force =  Seek( peoples[n]->position[(PEOPLE_POSITION_MEMORY - 1)], position);
         //   Vec2DNormalize(&force)
         force.x *= frameTime * -0.03;
         force.y *= frameTime * -0.03;
         peoples[n]->force = force;
    }
    oldPosition = position;

    // update state
    enum STATES state =  pCurrentState->update();
    if(state != pCurrentState->getState())
    {
        // change state
        pCurrentState = pStateVault->requestNewState(state,pCurrentState->getID());
        curAction = pCurrentState->getNextAction();
        switch (curAction)
        {
        case(LEAVETOEXIT):
            {
                sf::Vector2f exitPosition = pArea->getClosestExit(this->position);
                if (pPath != NULL) { delete pPath; pPath = NULL;}

                pPath = pPathFinder->findPath(position,exitPosition);
                nextNode = pPath->getNextVector();
            }
        // To Do add more action init logic
        }
    }

    //update logic of crowd

    switch (curAction)
    {
        case(LEAVETOEXIT):
        {
            if( (position.x - nextNode.x)*(position.x - nextNode.x)+(position.y - nextNode.y)*(position.y - nextNode.y) < 100 && pPath->isLastVector() == false)
            {
                nextNode = pPath->getNextVector();
            }
            sf::Vector2f force = Seek(nextNode,position);
            force.x *= frameTime * 0.05;
            force.y *= frameTime * 0.05;
            position += force;
        }break;
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
    personShape.setRadius(1);

    sf::Vector2f avgPosition;
    int i;

    for(unsigned int n = 0; n< peoples.size(); n++)
    {
        avgPosition.x = 0;
        avgPosition.y = 0;
        for(i = 0; i < PEOPLE_POSITION_MEMORY; i++)
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

    if (pPath != NULL)
    {
        pPath->drawPath(window);
    }

    personShape.setPosition(nextNode);
    personShape.setFillColor(sf::Color::Black);
    window.draw(personShape);

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

