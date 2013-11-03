#include "../../include/Simulator/Simulation.hpp"

// public:
ClSimulation::ClSimulation(const sf::VideoMode &Mode)
{
    this->currentOffset.x = this->currentOffset.y = 0;
    this->Mode = Mode;

    ClFileHandler fH;
    fH.openFile("test.csv");
    pArea = fH.getArea();
    levelSize = pArea->getLevelSize();
    //createObjects();

    gameView.setSize(Mode.width,Mode.height);
    gameView.setCenter(Mode.width/2, Mode.height/2);

    pCrowdManager = new ClCrowdManager(pArea, pArea->getLevelSize());

    pCrowdManager->CreateCrowd(sf::Vector2f(600,350),150,100);
    pCrowdManager->CreateCrowd(sf::Vector2f(850,250),150,500);
    //        pCrowdManager->CreateCrowd(sf::Vector2f(800,750),150,500);

    pThreatManager = new ClThreatManager(pArea);

    elapsedTime.restart();
    curGameState = MENU;
}
ClSimulation::~ClSimulation()
{
    delete pArea;
    delete pCrowdManager;
    delete pThreatManager;
}

bool ClSimulation::update(sf::RenderWindow &window, bool mouseReleased)
{
    float frameTime = elapsedTime.getElapsedTime().asMilliseconds();
    float actualFrameTime = frameTime; // not changed by speed variable
    frameTime *= speed;
    elapsedTime.restart();

    if(curGameState==SIMULATION)
    {
        // Update Crowds Pathfinding Statemachine and Heatmap
        pCrowdManager->Update(frameTime, window);
        // Update Threats
        pThreatManager->update(window, mouseReleased);
    }
    // Update View
    calculateOffset(actualFrameTime);
    return true;
}

void ClSimulation::draw(sf::RenderWindow &window)
{
    window.setView(gameView);
    // Draw Background
    window.clear(pArea->getBgColor());
    if(curGameState==SIMULATION)
    {
        // Draw Crowds
        pCrowdManager->draw(window);
    }
    // Draw static / dynamic Objects
    pArea->draw(window);
    // Draw Threats
    pThreatManager->draw(window);

}
// private :

void ClSimulation::partitionCrowds(int totalVisitors)
{

    //Calculate the priorities to partition the crowds
    int sum = 0;
    int counter = pArea->getNumberOfStaticObjects();
    int priority[counter];
    sf::Vector2f sSize;
    unsigned int sType;
    for(int i = 0; i < counter; i++)
    {
        priority[i] = 0;
        sType = (int) pArea->getType(i);
        sSize = pArea->getSize(i);
        switch(sType)
        {
        case 0:
            priority[i] = 3;
            break;
        case 1:
            priority[i] = 2;
            break;
        case 2:
            priority[i] = 1;
            break;
        default:
            priority[i] = 0;
        }

        priority[i] = priority[i] * sSize.x * sSize.y;
        sum += priority[i];
    }

}


//obsolote
void ClSimulation::createObjects()
{
    ClFileHandler fH;

    fH.readLevel("test.csv", pArea);

}


void ClSimulation::calculateOffset(float frameTime)
{
    // 1. check for keyboard input (arrow keys)
    // 2. check for validity of the new offset


    currentOffset.x = currentOffset.y = 0;

    //1.
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        currentOffset.x -= 1 * frameTime;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        currentOffset.x +=1 * frameTime;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        currentOffset.y -=1 * frameTime;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        currentOffset.y+=1 * frameTime;
    }
    // 2.


    sf::Vector2f center = gameView.getCenter();
    // check whether view goes out of bounds in the x direction
    // if ( Left && Right )
    if (center.x-(this->Mode.width / 2) + currentOffset.x > 0 && center.x + (this->Mode.width / 2) + currentOffset.x <= levelSize.x  )
    {
        gameView.move(currentOffset.x, 0);

    }
    // check whether view goes out of bounds in the y direction
    // if ( Top && Bottom )
    if (center.y-(this->Mode.height/2)+currentOffset.y > 0 && center.y + (this->Mode.height / 2) + currentOffset.y <= levelSize.y )
    {
        gameView.move(0 ,currentOffset.y);
    }
}

void ClSimulation::updateSpeed(bool pause,bool normal, bool fastForward)
{
    if (pause)
    {
        ClSimulation::speed = 0;
    }
    else if (normal)
    {
        speed = 1;
    }
    else if (fastForward)
    {
        ClSimulation::speed++;
        if (ClSimulation::speed > 3)
        {
            ClSimulation::speed = 1;
        }
    }
}

int ClSimulation::speed = 1;

