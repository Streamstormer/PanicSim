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
    ClStatistic::rememberSpeed(ClSimulation::speed);
}

void ClSimulation::setTotalVisitors(int number)
{
    totalVisitors = number;
}

// public:
ClSimulation::ClSimulation(const sf::VideoMode &Mode, std::string filePath)
{
    visitorsSet = false;
    this->currentOffset.x = this->currentOffset.y = 0;
    this->Mode = Mode;

    mouseOffset.x = mouseOffset.y = 0;

    ClFileHandler fH;
    if(filePath == "")
        fH.openFile("test.csv");
    else
        fH.openFile(filePath);
    pArea = fH.getArea();
    levelSize = pArea->getLevelSize();
    //createObjects();

    gameView.setSize(Mode.width,Mode.height);
    gameView.setCenter(Mode.width/2, Mode.height/2);

    pDiagramm = new ClDiagramm();
    pStatistic = new ClStatistic(pDiagramm);
    pCrowdManager = new ClCrowdManager(pArea, pArea->getLevelSize(), pStatistic, pDiagramm);

    /*
    pCrowdManager->CreateCrowd(sf::Vector2f(600,350),150,100);
    pCrowdManager->CreateCrowd(sf::Vector2f(850,250),150,500);
    */
    //        pCrowdManager->CreateCrowd(sf::Vector2f(800,750),150,500);

    pThreatManager = new ClThreatManager(pArea, pStatistic, pCrowdManager->getHeatMap(), pDiagramm);

    elapsedTime.restart();
    curGameState = MENU;
}
ClSimulation::~ClSimulation()
{
    speed = 1;
    delete pArea;
    delete pCrowdManager;
    delete pThreatManager;
    delete pStatistic;
    delete pDiagramm;
}

bool ClSimulation::update(sf::RenderWindow &window, bool mouseReleased)
{
    float frameTime = elapsedTime.getElapsedTime().asMilliseconds();
    float actualFrameTime = frameTime; // not changed by speed variable or limiting of frameTime
    frameTime *= speed;
    elapsedTime.restart();


    // limit FrameTime

    if ( frameTime > 50) frameTime = 50;

    if(curGameState==SIMULATION)
    {
        if(speed != 0)
        {

            // Update Crowds Pathfinding Statemachine and Heatmap
            pCrowdManager->Update(frameTime, window);
        }


        // Update Threats
        pThreatManager->update(window, mouseReleased , mouseOffset);
    }
    // Update Statistic
    pStatistic->update(frameTime);
    // Update View
    calculateOffset(actualFrameTime);
    pArea->update(frameTime);
    return true;

}

void ClSimulation::draw(sf::RenderWindow &window)
{
    window.setView(gameView);
    // Draw Background
    window.clear(pArea->getBgColor());
    if(curGameState==STATISTICS)
    {
        // Draw Statistic in background
        pStatistic->drawStatistic(window);
        // Draw Crowds
        pCrowdManager->draw(window);
        // Draw static / dynamic Objects
        pArea->draw(window);
        // Draw Diagramm in front
        pStatistic->drawDiagramm(window);
    }
    if(curGameState==SIMULATION)
    {
        // Draw Crowds
        pCrowdManager->draw(window);
        // Draw static / dynamic Objects
        pArea->draw(window);
        // Draw Threats
        pThreatManager->draw(window);
    }
}

// private :
void ClSimulation::partitionCrowds(int totalVisitors)
{
    ClCrowdPartition myPartitioner;
    myPartitioner.partitionCrowds(totalVisitors, pArea, pCrowdManager);
}



void ClSimulation::setCurGameState(enum GameStates newGS)
{
    if(!visitorsSet)
    {
        if (newGS == SIMULATION)
        {
            partitionCrowds(totalVisitors);
            visitorsSet = true;
        }
    }
    curGameState = newGS;
}


//obsolote
void ClSimulation::createObjects()
{
    ClFileHandler fH;

    fH.readLevel("test.csv", pArea);

}

//changed by Patrick with adaptions of Bomb, Fire, Thread and Threadmanager.
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
        mouseOffset.x += currentOffset.x;

    }
    else
    {
        if(center.x-(this->Mode.width / 2) + currentOffset.x < 0)
        {
            gameView.move((this->Mode.width / 2)-center.x, 0);
            mouseOffset.x += ( (this->Mode.width / 2)-center.x );
        }
        if(center.x + (this->Mode.width / 2) + currentOffset.x >= levelSize.x )
        {
            gameView.move( (levelSize.x - (center.x+this->Mode.width / 2) ) , 0);
            mouseOffset.x += (levelSize.x - (center.x+this->Mode.width / 2) );
        }
    }
    // check whether view goes out of bounds in the y direction
    // if ( Top && Bottom )
    if (center.y-(this->Mode.height / 2) + currentOffset.y > 0 && center.y + (this->Mode.height / 2) + currentOffset.y <= levelSize.y )
    {
        gameView.move(0 ,currentOffset.y);
        mouseOffset.y += currentOffset.y;
    }
    else
    {
        if(center.y-(this->Mode.height / 2) + currentOffset.y < 0 )
        {
            gameView.move(0, (this->Mode.height/2)-center.y );
            mouseOffset.y += ( (this->Mode.height/2)-center.y );
        }
        if(center.y + (this->Mode.height / 2) + currentOffset.y >= levelSize.y)
        {
            gameView.move(0, (levelSize.y - (center.y+this->Mode.height/2) ) );
            mouseOffset.y += (levelSize.y - (center.y+this->Mode.height/2) );
        }

    }
}

int *ClSimulation::getTotalVisitors()
{
    return &totalVisitors;
}

