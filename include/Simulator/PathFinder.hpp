/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Patrick Senneka
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    create an object, then call the function findPath(Vector2f, Vector2f) and you will recive an ClPath with the shortest Path
---------------------------------------------------------------------------------------------------------------------------------------
*/
#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "Area.hpp"
#include "Node.hpp"
#include "Path.hpp"
#include <vector>



class ClPathFinder
{
    public:
        ClPathFinder(ClArea *pArea, float nodeDistance, const sf::Vector2f & areaSize);
        ~ClPathFinder();
        void draw(sf::RenderWindow & window);
        ClPath* findPath(const sf::Vector2f & Start, const sf::Vector2f & Ende);

    private:
        void createNodes();
        void setNodeWeight(int nodeID, int parentID);
        bool findPath(int startID, int endID, ClPath *Path);
        bool createPath(int startID, int endID, ClPath *Path);
        ClNode* getNodeByID(int id);
        int assignVectorNode(const sf::Vector2f & Position);

        bool tryToAddNode(const sf::Vector2i &here, int id);
        void tryToAddNeighbour(int index, int neighbour_id, bool visited);

        bool validConnection(int startNodeId, int endNodeId);

        void getTempNextNode (int neighbourId, int *pTempWeight, int *pTempNextNode);

        int nodeCounter;
        ClArea *pArea;
        float nodeDistance;
        sf::Vector2f areaSize;

        std::vector<ClNode *> Nodes;
        std::vector<ClNode *> OpenList;
};

#endif // PATHFINDER_H
