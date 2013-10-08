#ifndef CROWDMANAGER_HPP
#define CROWDMANAGER_HPP

#include "Area.hpp"
#include "Crowd.hpp"
#include "HeatMap.hpp"
#include <vector>

class ClCrowdManager
{
    public:
        ClCrowdManager(ClArea *pArea)
        {
            temp = false;
            drawClock.restart();
            this->pArea = pArea;
            //Create HeatMap
            sf::Vector2i numberOfCells(30,30);
            sf::Vector2i ScreenSize(800, 600);
            pHeatMap = new ClHeatMap(numberOfCells, ScreenSize);

        }
        ~ClCrowdManager()
        {
            for (int n = 0; n< Crowds.size(); n++)
            {
                delete Crowds[n];
            }
        }

        void Update(float frameTime)
        {
            // Update HeatMap

            pHeatMap->update();

            // Update Crowds

            int n;
            for(n=0;n<Crowds.size();n++)
            {
                if ( n== 0)
                {
                //     The first crowd is movable with the mouse for debugging purposes
                    Crowds[n]->Update(sf::Mouse::getPosition(),frameTime);
                }
                else
                {
                    Crowds[n]->Update(frameTime);
                }
            }
        }
        void Draw(sf::RenderWindow& window)
        {
            int n;
            pHeatMap->draw(window);
            for(n=0;n<Crowds.size();n++)
            {
                Crowds[n]->Draw(window);
            }
        }


        void CreateCrowd(sf::Vector2f position, float radius, int people)
        {
            // set people count does not work yet
            static int j =0;
            j++;

            // for debugging puposes: each crowd gets a different color
            if(j==0)
            {
            ClCrowd *Crowd = new ClCrowd(radius, pArea,sf::Color::White,position, people);
            pHeatMap->registerCrowd(Crowd);
            Crowds.push_back(Crowd);
            }
            else if (j==1)
            {

            ClCrowd *Crowd = new ClCrowd(radius, pArea,sf::Color::Red,position, people);
            pHeatMap->registerCrowd(Crowd);
            Crowds.push_back(Crowd);

            }
            else
            {
            ClCrowd *Crowd = new ClCrowd(radius, pArea,sf::Color::Green,position, people);
            pHeatMap->registerCrowd(Crowd);
            Crowds.push_back(Crowd);
            }

        }

    private:
        // delete Me
        sf::Clock drawClock;
        bool temp;
        //
        ClArea *pArea;
        ClHeatMap *pHeatMap;
        std::vector<ClCrowd *> Crowds;


};

#endif // CROWDMANGER_HPP
