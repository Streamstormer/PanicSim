#include "../../include/Simulator/Simulation.hpp"


int ClSimulation::speed = 1;
int ClSimulation::totalVisitors = 0;

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

void ClSimulation::setTotalVisitors(int number)
{
    totalVisitors = number;
}


// public:
ClSimulation::ClSimulation(const sf::VideoMode &Mode)
{
    visitorsSet = false;
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


    /*
    pCrowdManager->CreateCrowd(sf::Vector2f(600,350),150,100);
    pCrowdManager->CreateCrowd(sf::Vector2f(850,250),150,500);
    */
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
    int sum = 0;
    int counter = pArea->getNumberOfStaticObjects();
    int priority[counter];
    calculatePriorities(&sum, priority, counter);
    double persons;
    sf::Vector2f sPosition;
    sf::Vector2f sVector;
    ClStaticObject *pObject;
    for(int i = 0; i < counter; i++)
    {
        if(priority[i])
        {
            persons = (priority[i] * totalVisitors / sum);
            pObject = pArea->getObject(i+1);

            sPosition = pObject->getCenter();
            sVector = sf::Vector2f(1.5 * (pObject->getMiddleOfLine().x - sPosition.x), 1.5 * (pObject->getMiddleOfLine().y - sPosition.y));


/*
            sPosition.x = pObject->getPosition().x + (pObject->getSize().x / 2);
            sPosition.y = pObject->getPosition().y + (pObject->getSize().y / 2);

*/
            std::cout << "persons before: " << persons;
            if(! pArea->attractionWithHigherId(i+2))
            {
                persons += (double) (totalVisitors - *(pCrowdManager->getPeopleCount()) - persons);
            }
            std::cout << "persons after: " << persons;

            pCrowdManager->CreateCrowd(sf::Vector2f(sPosition.x + sVector.x, sPosition.y + sVector.y),5,(int) persons);
        }
    }
}

void ClSimulation::calculatePriorities(int *sum, int *priority, int counter)
{
    sf::Vector2f sSize;
    enum staticObjects sType;
    for(int i = 0; i < counter; i++)
    {
        priority[i] = 0;
        sType = pArea->getType(i+1);
        sSize = pArea->getSize(i+1);
        switch(sType)
        {
        case 0:
            priority[i] = STAGE;
            break;
        case 1:
            priority[i] = BAR;
            break;
        case 2:
            priority[i] = WC;
            break;
        default:
            priority[i] = 0;
        }

        priority[i] = priority[i] * sSize.x * sSize.y / 1000;
        *sum += priority[i];
    }

}

void ClSimulation::setCurGameState(enum GameStates newGS)
{
    if(!visitorsSet){
    if (newGS == SIMULATION)
    {
        partitionCrowds(totalVisitors);
        visitorsSet = true;
    }
    curGameState = newGS;
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
