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
        // Update Crowds Pathfinding Statemachine and Heatmap
        pCrowdManager->Update(frameTime, window);
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
    ClFastSquareroot fSR;
    int sum = 0;
    int counter = pArea->getNumberOfStaticObjects();
    int priority[counter];
    calculatePriorities(&sum, priority, counter);
    double persons;
    sf::Vector2f sPosition;
    sf::Vector2f sVector;
    sf::Vector2f sUnitVector;
    sf::Vector2f vCrowdCandidate;
    sf::Vector2f vCandidateWa;
    double vectorDistance;

    int attractionLength;
    int numOfCrowds;
    int personsPerCrowd;

    ClStaticObject *pObject;
    ClPathFinder *pPF = new ClPathFinder(pArea, PATH_TEST_GRANULARITY, pArea->getLevelSize());
    ClPath *pPath = NULL;


    const int vMaxX = pArea->getLevelSize().x - 5;
    const int vMaxY = pArea->getLevelSize().y - 5;


    for(int i = 0; i < counter; i++)
    {
        if(priority[i])
        {
            persons = (priority[i] * totalVisitors / sum);
            pObject = pArea->getObject(i+1);

            sPosition = pObject->getCenter();
            sVector = sf::Vector2f(2.0 * (pObject->getMiddleOfLine().x - sPosition.x), 1.5 * (pObject->getMiddleOfLine().y - sPosition.y));
            vectorDistance = fSR.getSqrt(std::pow(sVector.x,2) + std::pow(sVector.y,2));
            if(vectorDistance != 0)
            {
                sUnitVector.x = sVector.x / vectorDistance;
                sUnitVector.y = sVector.y / vectorDistance;
            }
            else
            {
                std::cout << "Division by zero when calculating the Unit vector.";
            }
            //std::cout << "persons before: " << persons;
            /*******IF THIS IS THE LAST PLACEMENT OF A CROWD, THE INACCURACY FOR TOTAL VISITORS IS CORRECTED*********/
            if(! pArea->attractionWithHigherId(i+2))
            {
                persons += (double) (totalVisitors - *(pCrowdManager->getPeopleCount()) - persons);
            }

            // pObject->getSize().x is always the attraction length
            attractionLength = pObject->getSize().x;


            numOfCrowds = attractionLength / DIST_CROWDS_PER_ATTR;
            if(!numOfCrowds)
            {
                numOfCrowds = 1;
            }

            /*****Calculation candidate for Crowd positioning*****/
            vCrowdCandidate.x = sPosition.x + sVector.x + (POS_TRY_GRAN * sUnitVector.x);
            vCrowdCandidate.y = sPosition.y + sVector.y + (POS_TRY_GRAN * sUnitVector.y);
            if(abs(sUnitVector.x) < abs(sUnitVector.y))
            {
                if(numOfCrowds > 1)
                {
                    vCrowdCandidate.x -= numOfCrowds * DIST_CROWDS_PER_ATTR / 2 - DIST_CROWDS_PER_ATTR / 2;
                }
            }else
            {
                if(numOfCrowds > 1)
                {
                    vCrowdCandidate.y -= numOfCrowds * DIST_CROWDS_PER_ATTR / 2 - DIST_CROWDS_PER_ATTR / 2;
                }
            }


            for(int j = 0; j < numOfCrowds; j++)
            {
                if(pPath != NULL)
                {
                    delete pPath;
                }
                pPath = pPF->findPath(vCrowdCandidate,
                pArea->getClosestExit(vCrowdCandidate));



                vCandidateWa = vCrowdCandidate;
                while(pPath == NULL)
                {
                    if((vCandidateWa.x + (POS_TRY_GRAN * sUnitVector.x)) > 5
                            && vCandidateWa.x + (POS_TRY_GRAN * sUnitVector.x) < vMaxX
                            && vCandidateWa.y + (POS_TRY_GRAN * sUnitVector.y) > 5
                            && vCandidateWa.y + (POS_TRY_GRAN * sUnitVector.y) < vMaxY)
                    {
                        vCandidateWa.x += POS_TRY_GRAN * sUnitVector.x;
                        vCandidateWa.y += POS_TRY_GRAN * sUnitVector.y;
                        delete pPath;
                        pPath = pPF->findPath(sf::Vector2f(sPosition.x + sVector.x, sPosition.y + sVector.y), pArea->getClosestExit(sf::Vector2f(sPosition.x + sVector.x, sPosition.y + sVector.y)));
                    }
                    else
                    {
                        std::cout << "Not able to place crowd with id" << (i + 1);
                    }
                }
                personsPerCrowd = persons / numOfCrowds;
                if(j == numOfCrowds - 1)
                    personsPerCrowd += (persons - personsPerCrowd * numOfCrowds);
                pCrowdManager->CreateCrowd(vCandidateWa,(int)(persons / 50) + 10, personsPerCrowd);
                if(abs(sUnitVector.x) < abs(sUnitVector.y))
                {
                    vCrowdCandidate.x += DIST_CROWDS_PER_ATTR;
                }else
                {
                    vCrowdCandidate.y += DIST_CROWDS_PER_ATTR;
                }
            }
        }
    }
    delete pPath;
    delete pPF;
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
        case STAGE:
            priority[i] = 3;
            break;
        case BAR:
            priority[i] = 2;
            break;
        case WC:
            priority[i] = 5;
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
    if(!visitorsSet)
    {
        if (newGS == SIMULATION)
        {
            partitionCrowds(totalVisitors);
            visitorsSet = true;
     //       pStatistic->startTimer();
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
