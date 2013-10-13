#include "../../include/Simulator/Simulation.hpp"

    // public:
        ClSimulation::ClSimulation(const sf::VideoMode &Mode)
        {

            // Replace by FileHandler
            this->LevelSize.x = 2000;
            this->LevelSize.y = 2000;
            // End Replace

            this->currentOffset.x = this->currentOffset.y = 0;
            this->Mode = Mode;
            pArea = new ClArea;
            createObjects();

            gameView.setSize(Mode.width,Mode.height);
            gameView.setCenter(Mode.width/2, Mode.height/2);

            pCrowdManager = new ClCrowdManager(pArea, sf::Vector2i(Mode.width,Mode.height));

            pCrowdManager->CreateCrowd(sf::Vector2f(300,250),150,800);
            pCrowdManager->CreateCrowd(sf::Vector2f(550,350),150,700);
            pCrowdManager->CreateCrowd(sf::Vector2f(250,523),150,650);

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
            frameTime *= speed;
            elapsedTime.restart();
            // Update Crowds Pathfinding Statemachine and Heatmap
            pCrowdManager->Update(frameTime);
            // Update View
            calculateOffset(frameTime);

            return true;
        }
        void ClSimulation::draw(sf::RenderWindow &window)
        {


            window.setView(gameView);
            // Draw Background
            pArea->draw(window);
            // Draw Crowds
            pCrowdManager->Draw(window);

        }
        // private :

        void ClSimulation::createObjects()
        {
            // FileHandler goes here
            ClFileHandler fH;
            fH.readLevel("test.csv", pArea);
            pArea->insertStObj(FENCE, sf::Vector2f(300,300),sf::Vector2f(1590,1590),0);

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
            if (center.x-(this->Mode.width / 2) + currentOffset.x > 0 && center.x + (this->Mode.width / 2) + currentOffset.x <= LevelSize.x  )
            {
                    gameView.move(currentOffset.x, 0);

            }
            // check whether view goes out of bounds in the y direction
            // if ( Top && Bottom )
            if (center.y-(this->Mode.height/2)+currentOffset.y > 0 && center.y + (this->Mode.height / 2) + currentOffset.y <= LevelSize.y )
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
            std::cout << "speed :" << ClSimulation::speed << std::endl;
        }

        int ClSimulation::speed = 1;

