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
        do
        {
            newPerson->position.x = std::rand();
            newPerson->position.x = (int)newPerson->position.x % (int)(2*radius);
            newPerson->position.x -= radius;
        } while (newPerson->position.x < 0);

        do
        {
            newPerson->position.y = std::rand();
            newPerson->position.y = (int)newPerson->position.y % (int)(2*radius);
            newPerson->position.y -= radius;
        } while (newPerson->position.y < 0);
        newPerson->position.x += position.x ;
        newPerson->position.y += position.y;

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
    float movementFactor = 1.0f;
    if(position == oldPosition)
    {
        movementFactor = 0.75f;
    }
    sf::Vector2f force;
     for (unsigned int n = 0; n < peoples.size(); n++)
    {
        // Center Force
            force =  Seek( peoples[n]->position, position, sf::Vector2f(0,0));
         //   Vec2DNormalize(&force)
         force.x *= frameTime * 0.03;
         force.y *= frameTime * 0.03;
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
            if( (position.x - nextNode.x)*(position.x - nextNode.x)+(position.y - nextNode.y)*(position.y - nextNode.y) < 100 )
            {
                nextNode = pPath->getNextVector();
            }
            sf::Vector2f force = Seek(nextNode,position, sf::Vector2f(0,0));
            force.x *= frameTime * -0.01;
            force.y *= frameTime * -0.01;
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
    for(unsigned int n = 0; n< peoples.size(); n++)
    {
        personShape.setPosition(peoples[n]->position);
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

sf::Vector2f ClCrowd::Seek(sf::Vector2f TargetPos, const sf::Vector2f & Destination, const sf::Vector2f & CurVelocity)
{
    TargetPos.x -= Destination.x;
    TargetPos.y -= Destination.y;
  //  float helpVar = (TargetPos.x + TargetPos.y)*(TargetPos.x * TargetPos.y);
  //  helpVar = sqrt(helpVar);
    Vec2DNormalize(&TargetPos);

 //   TargetPos.x *= helpVar;
 //   TargetPos.y *= helpVar;
    return (-TargetPos );
}

