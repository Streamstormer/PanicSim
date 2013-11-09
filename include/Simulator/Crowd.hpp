
#ifndef CROWD_HPP_INCLUDED
#define CROWD_HPP_INCLUDED

#include "Area.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "HeatMap.hpp"
#include "People.hpp"
#include "StateEngine/StateVault.hpp"
#include "PathFinder.hpp"

class ClCrowd
{
public:
    ClCrowd(float radius, ClArea * pArea, sf::Color Color, sf::Vector2f position, int numOfPeoples, ClHeatMap * pHeatMap, ClStateVault *pStateVault, ClPathFinder *pPathfinder);
    ~ClCrowd();

    void Update(sf::Vector2i position,float frameTime);
    void Update(float frameTime);
    void Draw(sf::RenderWindow& window);

    const sf::Vector2f  getMassPoint();
    float getRadius();

private:

    void Vec2DNormalize( sf::Vector2f *NormalizeMe );
    sf::Vector2f Seek(sf::Vector2f TargetPos, const sf::Vector2f & Destination);

    ClArea *pArea;       // used for finding the exit
    ClHeatMap *pHeatMap; // used for human - human collision detection
    ClPathFinder *pPathFinder;
    ClPath *pPath;

    ClStateVault *pStateVault;          // used to determine what to do next
    ClAbstractState *pCurrentState;     // current update logic
    enum ACTIONS curAction;             // current update logic

    std::vector<StrPeople *> peoples;
    sf::Vector2f position;
    sf::Vector2f oldPosition;

    sf::Vector2f nextNode;

    float radius;

    //panic = false when there were no casualties yet
    //panic = true when there is at least one casualtie
    bool panic;

    // for debugging puposes : each Crowd does have a unique color
    sf::Color Color;


};

#endif // CROWD2_HPP_INCLUDED
