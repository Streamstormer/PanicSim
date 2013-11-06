#include "../../include/Simulator/CrowdManager.hpp"

ClCrowdManager::ClCrowdManager(ClArea *pArea, const sf::Vector2i &ScreenSize, ClStatistic *pStatistic)
{
    this->pArea = pArea;
    this->pStatistic = pStatistic;
    //Create HeatMap
    sf::Vector2i numberOfCells(40,40);
    pHeatMap = new ClHeatMap(numberOfCells, ScreenSize, pArea, pStatistic);
    pPathFinder = new ClPathFinder(pArea, 100,sf::Vector2i(ScreenSize.x,ScreenSize.y));
    pStateVault = new ClStateVault();
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
       // debugging of mouse with or without (window)
       //     sf::Vector2i fWindow = sf::Mouse::getPosition(window);
       //     sf::Vector2i fnoWindow = sf::Mouse::getPosition();

     //       std::cout  << "fWindow x / y" << fWindow.x << " / " << fWindow.y << std::endl;
    //        std::cout  << "fnoWindow x / y" << fnoWindow.x << " / " << fnoWindow.y << std::endl;

            Crowds[n]->Update(/*sf::Mouse::getPosition(window),*/frameTime);
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
}


void ClCrowdManager::CreateCrowd(sf::Vector2f position, float radius, int people)
{
    static int j =0;
    // increment people for SimpleGUI
    ClCrowdManager::addPeople(people);

    // for debugging puposes: each crowd gets a different color
    if(j==0)
    {
        ClCrowd *Crowd = new ClCrowd(radius, pArea,sf::Color::Black,position, people, pHeatMap, pStateVault,pPathFinder);
        Crowds.push_back(Crowd);
    }
    else if (j==1)
    {

        ClCrowd *Crowd = new ClCrowd(radius, pArea,sf::Color::Red,position, people, pHeatMap, pStateVault,pPathFinder);
        Crowds.push_back(Crowd);

    }
    else
    {
        ClCrowd *Crowd = new ClCrowd(radius, pArea,sf::Color::Blue,position, people, pHeatMap, pStateVault,pPathFinder);
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

ClHeatMap* ClCrowdManager::getHeatMap()
{
     return pHeatMap;
}
