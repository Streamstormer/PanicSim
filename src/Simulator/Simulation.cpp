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

            pGUI = new ClSimpleGUI(sf::Vector2f(Mode.width, Mode.height));
            elapsedTime.restart();
        }
        ClSimulation::~ClSimulation()
        {
            delete pArea;
            delete pCrowdManager;
            delete pGUI;
        }
        bool ClSimulation::update(sf::RenderWindow &window)
        {
            float frameTime = elapsedTime.getElapsedTime().asMilliseconds();
            elapsedTime.restart();
            // Update Crowds Pathfinding Statemachine and Heatmap
            pCrowdManager->Update(frameTime);
            // Update GUI
            pGUI->update(window);
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
            // Draw GUI
            // reset View so GUI is drawn at the same position everytime
            window.setView(window.getDefaultView());
            pGUI->draw(window);
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



