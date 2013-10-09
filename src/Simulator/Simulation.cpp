#include "../../include/Simulator/Simulation.hpp"

    // public:
        ClSimulation::ClSimulation(const sf::VideoMode &Mode)
        {
            this->Mode = Mode;
            pArea = new ClArea;
            CreateObjects();
            pCrowdManager = new ClCrowdManager(pArea, sf::Vector2i(Mode.width,Mode.height));

            pCrowdManager->CreateCrowd(sf::Vector2f(300,250),150,600);
            pCrowdManager->CreateCrowd(sf::Vector2f(550,350),150,500);
            pCrowdManager->CreateCrowd(sf::Vector2f(250,523),150,150);

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
            float frameTime = elapsedTime.getElapsedTime().asSeconds();
            // Update Crowds Pathfinding Statemachine and Heatmap
            pCrowdManager->Update(frameTime);
            // Update GUI
            pGUI->update(window);

            return true;
        }
        void ClSimulation::draw(sf::RenderWindow &window)
        {
            // Draw Background
            pArea->draw(window);
            // Draw Crowds
            pCrowdManager->Draw(window);
            // Draw GUI
            pGUI->draw(window);
        }
        // private :

        void ClSimulation::CreateObjects()
        {
            // FileHandler goes here
            // Dummy Logic
            pArea->insertStObj(STAGE, sf::Vector2f(50,100), sf::Vector2f(250,120),90);
            pArea->insertStObj(BAR, sf::Vector2f(120,350), sf::Vector2f(500,200),0);
            pArea->insertStObj(WC, sf::Vector2f(150,80), sf::Vector2f(40,400),0);
            ClFileHandler fH;
            fH.writeLevel("test", pArea);

        }


