#include "../../include/Simulator/Simulation.hpp"

    // public:
        ClSimulation::ClSimulation(const sf::VideoMode &Mode)
        {
            ClFileHandler fH;
            fH.openFile("test.csv");
            /*
            levelSize = fH.getLevelSize();
            */

            this->currentOffset.x = this->currentOffset.y = 0;
            this->Mode = Mode;
            pArea = fH.getArea();
            //createObjects();

            gameView.setSize(Mode.width,Mode.height);
            gameView.setCenter(Mode.width/2, Mode.height/2);

            pCrowdManager = new ClCrowdManager(pArea, pArea->getLevelSize());

            pCrowdManager->CreateCrowd(sf::Vector2f(600,550),150,1000);
            pCrowdManager->CreateCrowd(sf::Vector2f(850,250),150,500);
            pCrowdManager->CreateCrowd(sf::Vector2f(800,750),150,500);



            elapsedTime.restart();
        }
        ClSimulation::~ClSimulation()
        {
            delete pArea;
            delete pCrowdManager;
        }
        bool ClSimulation::update(sf::RenderWindow &window)
        {
            float frameTime = elapsedTime.getElapsedTime().asMilliseconds();
            float actualFrameTime = frameTime; // not changed by speed variable
            frameTime *= speed;

            elapsedTime.restart();
            // Update Crowds Pathfinding Statemachine and Heatmap
            pCrowdManager->Update(frameTime, window);
            // Update View
            calculateOffset(actualFrameTime);

            return true;
        }
        void ClSimulation::draw(sf::RenderWindow &window)
        {
            window.setView(gameView);
            // Draw Background
            window.clear(pArea->getBgColor());
            // Draw Crowds
            pCrowdManager->draw(window);
            // Draw static / dynamic Objects
            pArea->draw(window);

        }
        // private :


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

