#ifndef CROWDMANAGER_HPP
#define CROWDMANAGER_HPP

#include "Area.hpp"
#include "Crowd.hpp"
#include <vector>

class ClCrowdManager
{
    public:
        ClCrowdManager(ClArea *pArea) {this->pArea = pArea;}
        ~ClCrowdManager() {}

        void Update(float frameTime)
        {
            int n;
            for(n=0;n<Crowds.size();n++)
            {
                if ( n== 0)
                {
                //     The first crowd is movable with the mouse for debugging purposes
                    Crowds[n].Update(sf::Mouse::getPosition(),frameTime);
                }
                else
                {
                    Crowds[n].Update(frameTime);
                }
            }
        }
        void Draw(sf::RenderWindow& window)
        {
            int n;
            for(n=0;n<Crowds.size();n++)
            {
                Crowds[n].Draw(window);
            }
        }


        void CreateCrowd(sf::Vector2f position, float radius, int people)
        {
            // set people count does not work yet
            // 500 by default
            static int j =0;
            j++;

            // for debugging puposes: each crowd gets a different color
            if(people==0)
            {
            ClCrowd Crowd(radius, pArea,sf::Color::White,position);
            Crowds.push_back(Crowd);
            }
            else if (people==1)
            {

            ClCrowd Crowd(radius, pArea,sf::Color::Red,position);
            Crowds.push_back(Crowd);

            }
            else if (people==2)
            {

            ClCrowd Crowd(radius, pArea,sf::Color::Green,position);
            Crowds.push_back(Crowd);

            }

        }

    private:

        ClArea *pArea;
        std::vector<ClCrowd> Crowds;


};

#endif // CROWDMANGER_HPP
