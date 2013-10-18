#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "Area.hpp"
#include "Node.hpp"
#include <vector>



class ClPathFinder
{
    public:
        ClPathFinder(ClArea *pArea, float nodeDistance, const sf::Vector2f & areaSize);
        ~ClPathFinder();
        void draw(sf::RenderWindow & window);
        bool findPath(int startID, int endID);
        void drawPath(sf::RenderWindow & window);

    private:
        void createNodes();
        void setNodeWeight(int nodeID, int parentID);
        void createPath(int startID, int endID);

        int nodeCounter;
        ClArea *pArea;
        float nodeDistance;
        sf::Vector2f areaSize;

        std::vector<ClNode *> Nodes;
        std::vector<ClNode *> OpenList;
        std::vector<ClNode *> Path;
};

#endif // PATHFINDER_H
