#include "../../include/Simulator/CrowdManager.hpp"


ClCrowdManager::ClCrowdManager(ClArea *pArea, const sf::Vector2i &ScreenSize)
{
    this->pArea = pArea;
    //Create HeatMap
    sf::Vector2i numberOfCells(70,70);
    pHeatMap = new ClHeatMap(numberOfCells, ScreenSize);
    pPathFinder = new ClPathFinder(pArea, 100,sf::Vector2f(ScreenSize.x,ScreenSize.y));

}
ClCrowdManager::~ClCrowdManager()
{
    for (unsigned int n = 0; n< Crowds.size(); n++)
    {
        delete Crowds[n];
    }
}

void ClCrowdManager::Update(float frameTime, sf::RenderWindow &window)
{

    // Update Crowds

    unsigned int n;
    for(n=0; n<Crowds.size(); n++)
    {
        if ( n== 0)
        {
            //     The first crowd is movable with the mouse for debugging purposes
            Crowds[n]->Update(sf::Mouse::getPosition(window),frameTime);
        }
        else
        {
            Crowds[n]->Update(frameTime);
        }
    }
    // Update HeatMap
    pHeatMap->update(frameTime);
}
void ClCrowdManager::draw(sf::RenderWindow& window)
{
    unsigned int n;
    pHeatMap->draw(window);
    for(n=0; n<Crowds.size(); n++)
    {
        Crowds[n]->Draw(window);
    }

    sf::Vector2f TestPosition1(20,80);
    sf::Vector2f TestPosition2(320,580);
    pPathFinder->draw(window);
    (pPathFinder->findPath(TestPosition1, TestPosition2))->drawPath(window);


}


void ClCrowdManager::CreateCrowd(sf::Vector2f position, float radius, int people)
{
    // set people count does not work yet
    static int j =0;
    // increment people for SimpleGUI
    ClCrowdManager::addPeople(people);

    // for debugging puposes: each crowd gets a different color
    if(j==0)
    {
        ClCrowd *Crowd = new ClCrowd(radius, pArea,sf::Color::White,position, people, pHeatMap);
        Crowds.push_back(Crowd);
    }
    else if (j==1)
    {

        ClCrowd *Crowd = new ClCrowd(radius, pArea,sf::Color::Red,position, people, pHeatMap);
        Crowds.push_back(Crowd);

    }
    else
    {
        ClCrowd *Crowd = new ClCrowd(radius, pArea,sf::Color::Green,position, people, pHeatMap);
        Crowds.push_back(Crowd);
    }
    j++;

}
// Static Functions for the Simple Labels
int *ClCrowdManager::getPeopleCount()
{
    return &peopleCount;
}

void ClCrowdManager::addPeople(int Number)
{
    peopleCount +=Number;
}

int ClCrowdManager::peopleCount = 0;
