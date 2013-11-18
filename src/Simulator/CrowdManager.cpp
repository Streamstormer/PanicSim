#include "../../include/Simulator/CrowdManager.hpp"

ClCrowdManager::ClCrowdManager(ClArea *pArea, const sf::Vector2i &ScreenSize, ClStatistic *pStatistic, ClDiagramm *pDiagramm)
{
    this->pArea = pArea;
    this->pStatistic = pStatistic;
    //Create HeatMap (CELLNUMBER = 40)
    sf::Vector2i numberOfCells(CELLNUMBER,CELLNUMBER);
    pHeatMap = new ClHeatMap(numberOfCells, ScreenSize, pArea, pStatistic, pDiagramm);

    pPathFinder = new ClPathFinder(pArea, 50,sf::Vector2i(ScreenSize.x,ScreenSize.y));
    pStateVault = new ClStateVault();
}

ClCrowdManager::~ClCrowdManager()
{
    for (unsigned int n = 0; n< Crowds.size(); n++)
    {
        delete Crowds[n];
    }
    peopleCount = 0;
    delete pHeatMap;
    delete pPathFinder;
    delete pStateVault;
}

void ClCrowdManager::clean()
{
    for(unsigned int n = 0; n < Crowds.size(); n++)
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
        Crowds[n]->Update(frameTime);
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
    //pPathFinder->draw(window);
}


void ClCrowdManager::CreateCrowd(sf::Vector2f position, float radius, int people)
{
        // increment people for SimpleGUI
        ClCrowdManager::addPeople(people);

        ClCrowd *Crowd = new ClCrowd(radius, pArea,sf::Color::Blue,position, people, pHeatMap, pStateVault, pPathFinder);
        Crowds.push_back(Crowd);
}
// Static Functions for the Simple Labels
int *ClCrowdManager::getPeopleCount()
{
    return &peopleCount;
}

void ClCrowdManager::addPeople(int Number)
{
    peopleCount += Number;
}

int ClCrowdManager::peopleCount = 0;

ClHeatMap* ClCrowdManager::getHeatMap()
{
     return pHeatMap;
}
