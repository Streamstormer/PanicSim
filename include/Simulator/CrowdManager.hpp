#ifndef CROWDMANAGER_HPP
#define CROWDMANAGER_HPP

#include "Area.hpp"
#include "Crowd.hpp"
#include "HeatMap.hpp"
#include <vector>

class ClCrowdManager
{
    public:
        ClCrowdManager(ClArea *pArea, const sf::Vector2i &ScreenSize);
        ~ClCrowdManager();

        void Update(float frameTime);
        void Draw(sf::RenderWindow& window);
        void CreateCrowd(sf::Vector2f position, float radius, int people);

    private:

        ClArea *pArea;
        ClHeatMap *pHeatMap;
        std::vector<ClCrowd *> Crowds;
};

#endif // CROWDMANGER_HPP
