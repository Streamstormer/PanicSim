
#ifndef CROWD_2HPP_INCLUDED
#define CROWD_2HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <math.h>
#define MAXPPL 100
#define MAXSPEED 0.1f

struct StrPeople
{
    sf::Vector2f position;
    sf::Vector2f forceVec;
};

void Vec2DNormalize( sf::Vector2f *NormalizeMe )
{
    if (NormalizeMe->x != 0 && NormalizeMe->y != 0)
    {

    float helpVar = fabs(NormalizeMe->x) + fabs(NormalizeMe->y);
    NormalizeMe->x /= helpVar;
    NormalizeMe->y /= helpVar;
    }
}

sf::Vector2f Seek(sf::Vector2f TargetPos, const sf::Vector2f & Destination, const sf::Vector2f & CurVelocity)
{
    TargetPos.x -= Destination.x;
    TargetPos.y -= Destination.y;

    Vec2DNormalize(&TargetPos);

    return (-TargetPos - CurVelocity );
}

float invert(float Max, float Current)
{
    return abs(Current - Max);
}

sf::Vector2f DistanceForce(StrPeople* start,  int current)
{
    int n;

    sf::Vector2f delta;
    sf::Vector2f force(0,0);
    int NbCount = 0;

    for ( n = 0; n< MAXPPL; n++)
    {
        if ( n != current)
        {
            delta.x =   (start[current].position.x-start[n].position.x );
            delta.y =  ( start[current].position.y-start[n].position.y );

            if (((delta.x*delta.x) + (delta.y * delta.y)) < 60)
            {
                force.x += delta.x;
                force.y += delta.y;
                NbCount ++;
            }

        }
    }
    delta.x /= NbCount;
    delta.y /= NbCount;
    Vec2DNormalize(&force);
    return -force;
}

sf::Vector2f Cohesion(StrPeople* start, const sf::Vector2f & massPoint, int current)
{
  //first find the center of mass of all the agents
  sf::Vector2f SteeringForce, CenterOfMass;

  int NeighborCount = 0;
  CenterOfMass.x  = CenterOfMass.y = 0;

  //iterate through the neighbors and sum up all the position vectors
  for (int n = 0; n<MAXPPL; n++)
  {
    //make sure *this* agent isn't included in the calculations and that
    //the agent being examined is close enough
    if(n != current)
    {
      CenterOfMass += start[n].position;
      ++NeighborCount;
    }
  }
  if (NeighborCount > 0)
  {
    //the center of mass is the average of the sum of positions
    CenterOfMass.x /= (double)NeighborCount;
    CenterOfMass.y /= (double)NeighborCount;

    //now seek towards that position
    SteeringForce = Seek(CenterOfMass, start[current].position, start[current].forceVec);
  }

  //the m,agnitude of cohesion is usually much larger than separation or
  //allignment so it usually helps to normalize it.
  Vec2DNormalize(&SteeringForce);
  return SteeringForce;
}

class ClCrowd
{
public:
    ClCrowd(float radius)
    {
        position.x = position.y = 250;
        this->radius = radius;
        sf::Vector2f mP = this->getMassPoint();

        //randomize the position of the people
        for (int n = 0; n < MAXPPL; n++)
        {
            peoples[n].position.x = std::rand();
            peoples[n].position.x = (int)peoples[n].position.x % (int)(2*radius);
            peoples[n].position.x -= radius;
            peoples[n].position.y = std::rand();
            peoples[n].position.y = (int)peoples[n].position.y % (int)(2*radius);
            peoples[n].position.y -= radius;

            peoples[n].position.x += mP.x;
            peoples[n].position.y += mP.y;

            peoples[n].forceVec.x = peoples[n].forceVec.y =0;
        }

    }
    ~ClCrowd() {}

    void update(sf::Vector2i position,float frameTime)
    {
        static int j;
             this->position.x = position.x;
             this->position.y = position.y;
             j++;

        for (int n = 0; n < MAXPPL; n++)
        {
//            if ( !(j %2))
           // peoples[n].forceVec = Cohesion(peoples,this->getMassPoint(), n);

           if ( (j % 2) )
            peoples[n].forceVec =  DistanceForce( peoples, n);
        if ( !(j%2))
            peoples[n].forceVec =  Seek( peoples[n].position, this->getMassPoint(), peoples[n].forceVec);

            peoples[n].position.x += peoples[n].forceVec.x * frameTime ;
            peoples[n].position.y += peoples[n].forceVec.y * frameTime ;
        }


    }

    void draw(sf::RenderWindow& window)
    {
        sf::CircleShape personShape;

        personShape.setFillColor(sf::Color::Blue);
        personShape.setRadius(1);
        for(int n = 0; n< MAXPPL; n++)
        {
            personShape.setPosition(peoples[n].position);
            window.draw(personShape);
        }
        personShape.setPosition(getMassPoint());
        personShape.setFillColor(sf::Color::Red);
        personShape.setRadius(5);
        window.draw(personShape);
    }

    const sf::Vector2f  getMassPoint()
    {
        sf::Vector2f massPoint;
        massPoint = position;
        massPoint.x -= radius;
        massPoint.y -= radius;
        return massPoint;
    }

    float getRadius()
    {
        return radius;
    }
private:
    struct StrPeople peoples[MAXPPL];
    sf::Vector2f position;
    float radius;
};

#endif // CROWD2_HPP_INCLUDED
