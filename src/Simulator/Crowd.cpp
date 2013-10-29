#include "../../include/Simulator/Crowd.hpp"


ClCrowd::ClCrowd(float radius, ClArea * pArea, sf::Color Color, sf::Vector2f position, int numOfPeoples, ClHeatMap *pHeatMap)
{
    this->position = position;
    oldPosition = position;
    this->Color = Color;

    this->radius = radius;
    sf::Vector2f mP = this->getMassPoint();
    this->pArea = pArea;
    this->pHeatMap = pHeatMap;

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
        newPerson->position.x += mP.x;
        newPerson->position.y += mP.y;

    //    newPerson->forceVec.x = newPerson->forceVec.y =0;

        peoples.push_back(newPerson);

    }

    // register people in the HeatMap

    pHeatMap->registerCrowd(peoples);

}
ClCrowd::~ClCrowd()
{
    for (unsigned int n = 0; n < peoples.size(); n++)
    {
        delete peoples[n];
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
            force =  Seek( peoples[n]->position, this->getMassPoint(), sf::Vector2f(0,0));
         //   Vec2DNormalize(&force);



            // check collision
            int id = pArea->getIdByVector(peoples[n]->position);
            if( id == -1)
            {
                peoples[n]->position.x += force.x * frameTime *0.03 * movementFactor;
                peoples[n]->position.y += force.y * frameTime *0.03 * movementFactor;
            }
            else
            {
                peoples[n]->position.x -= force.x * frameTime *0.03;
                peoples[n]->position.y -= force.y * frameTime *0.03;
            }
    }
    oldPosition = position;
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
    personShape.setPosition(getMassPoint());
    personShape.setFillColor(sf::Color::Red);
    personShape.setRadius(5);
    personShape.move(sf::Vector2f(-2.5,-2.5));
    window.draw(personShape);
}

const sf::Vector2f ClCrowd::getMassPoint()
{
    sf::Vector2f massPoint;
    massPoint = position;
    massPoint.x -= radius;
    massPoint.y -= radius;
    return massPoint;
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

