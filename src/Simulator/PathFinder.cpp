#include "../../include/Simulator/PathFinder.hpp"

ClPathFinder::ClPathFinder(ClArea *pArea, float nodeDistance, const sf::Vector2f & areaSize)
{
    this->pArea = pArea;
    this->nodeDistance = nodeDistance;
    this->areaSize = areaSize;
    nodeCounter = 0;
    createNodes();
    //findPath(15, 10);



}

ClPathFinder::~ClPathFinder()
{
    for(unsigned int n = 0; n < Nodes.size(); n++)
    {
        delete Nodes[n];
    }
}
/*
---------------------------------------------------------------------------------------------------------------------------------------
name:   createNodes()
---------------------------------------------------------------------------------------------------------------------------------------
return value: none
---------------------------------------------------------------------------------------------------------------------------------------
createNodes() creates Nodes with the x and y distance of nodeDistance.
Nodes are only created if the position is valid (not in a static object)
---------------------------------------------------------------------------------------------------------------------------------------
*/
void ClPathFinder::createNodes()
{
    ClNode *pAddMe;
    sf::Vector2f testPos;
    nodeCounter=0;
    //idArray is used to assign the top, left, right and below neighbour faster
    int sizeIdArrayX = (int)areaSize.x/nodeDistance;
    int sizeIdArrayY = (int)areaSize.y/nodeDistance;
    int idArray [sizeIdArrayX][sizeIdArrayY];
    int tempX,tempY;

    for(int i=0; i<sizeIdArrayX; i++)
    {
        for(int j=0; j<sizeIdArrayY; j++)
        {
            idArray[i][j] = -1;
        }
    }

    for(testPos.x = 0; testPos.x < areaSize.x-nodeDistance; testPos.x += nodeDistance)
    {
        for(testPos.y = 0; testPos.y < areaSize.y-nodeDistance; testPos.y += nodeDistance)
        {
            tempX = (int)testPos.x/nodeDistance;
            tempY = (int)testPos.y/nodeDistance;
            if(pArea->validPoint(testPos))
            {
                pAddMe = new ClNode(testPos, nodeCounter);
                Nodes.push_back(pAddMe);
                //idArray stores the nodeCounter at the position of nodeposition/nodeDistance
                idArray [tempX][tempY] = nodeCounter;
                nodeCounter++;
            }
            else
                //idArray stores -1 id the node does not exist
                idArray [tempX][tempY] = -1;
        }
    }
    for(int i=0; i<sizeIdArrayY; i++)
    {
        for(int j=0; j<sizeIdArrayX; j++)
        {
            //std::cerr<<"hallo"<<" "<<std::endl;
            std::cerr<<idArray[i][j]<<" ";
        }
        std::cerr<<" "<<std::endl;
    }
    //the neighbours of the nodes are set here
    for(int k=0; k<(int)Nodes.size(); k++)
    {
        tempX = (int)(Nodes[k]->get_x_position()/nodeDistance);
        tempY = (int)(Nodes[k]->get_y_position()/nodeDistance);
        int tempLeftX = (tempX-1);
        int tempRightX = (tempX+1);
        int tempTopY = (tempY-1);
        int tempBelowY = (tempY+1);
        //top neighbour
        if(idArray[tempX][tempTopY] != -1 && tempTopY >= 0)
        {
            Nodes[k]->set_neighbour_id_top(idArray[tempX][tempTopY]);
            std::cerr<<Nodes[k]->getID()<<" t"<<idArray[tempX][tempTopY]<<"|";
        }
        else
        {
            Nodes[k]->set_neighbour_id_top(-1);
            std::cerr<<Nodes[k]->getID()<<" t"<<idArray[tempX][tempTopY]<<"|";
        //below neighbour
        }
        if(idArray[tempX][tempBelowY] != -1 && tempBelowY <= (int)areaSize.y)
        {
            Nodes[k]->set_neighbour_id_below(idArray[tempX][tempBelowY]);
            std::cerr<<Nodes[k]->getID()<<" b"<<idArray[tempX][tempTopY]<<"|";
        }
        else
        {
            Nodes[k]->set_neighbour_id_below(-1);
            std::cerr<<Nodes[k]->getID()<<" b"<<idArray[tempX][tempTopY]<<"|";
        }

        //left neighbour
        if(idArray[tempLeftX][tempY] != -1 && tempLeftX >= 0)
        {
            Nodes[k]->set_neighbour_id_left(idArray[tempLeftX][tempY]);
            std::cerr<<Nodes[k]->getID()<<" l"<<idArray[tempX][tempTopY]<<"|";
        }
        else
        {
            Nodes[k]->set_neighbour_id_left(-1);
            std::cerr<<Nodes[k]->getID()<<" l"<<idArray[tempX][tempTopY]<<"|";
        }

        //right neighbour
        if(idArray[tempRightX][tempY] != -1 && tempRightX <= (int)areaSize.x)
        {
            Nodes[k]->set_neighbour_id_right(idArray[tempRightX][tempY]);
            std::cerr<<Nodes[k]->getID()<<" r"<<idArray[tempX][tempTopY]<<"|";
        }
        else
        {
            Nodes[k]->set_neighbour_id_right(-1);
            std::cerr<<Nodes[k]->getID()<<" r"<<idArray[tempX][tempTopY]<<"|";
        }
        std::cerr <<std::endl;
    }
}
/*
---------------------------------------------------------------------------------------------------------------------------------------
name:   draw(sf::RenderWindow & window)
---------------------------------------------------------------------------------------------------------------------------------------
return value:   none
---------------------------------------------------------------------------------------------------------------------------------------
draw(sf::RenderWindow & window) is a test-function to validate if the createNodes() works proverly
The nodes are drawn on the screen.
---------------------------------------------------------------------------------------------------------------------------------------
*/
void ClPathFinder::draw(sf::RenderWindow & window)
{
    for(unsigned int n = 0; n < Nodes.size(); n++)
    {
        Nodes[n]->draw(window);
    }
}

/*
---------------------------------------------------------------------------------------------------------------------------------------
name:   findPath(int startID, int endID)
---------------------------------------------------------------------------------------------------------------------------------------
return value:   true if Path can be found       false if no Path exists
---------------------------------------------------------------------------------------------------------------------------------------

---------------------------------------------------------------------------------------------------------------------------------------
*/
bool ClPathFinder::findPath(int startID, int endID)
{
    if(startID == endID)
        return false;
    else
    {
        Nodes[endID]->set_visited(true);
        Nodes[endID]->set_weight(0);
        OpenList.push_back(Nodes[endID]);
    }
    while(OpenList.size() > 0)
    {
        int index = OpenList.front()->getID();

        if(Nodes[index]->get_neighbour_id_top() != -1 && Nodes[Nodes[index]->get_neighbour_id_top()]->get_visited() == false)
        {
            setNodeWeight(Nodes[index]->get_neighbour_id_top(), index);
            OpenList.push_back(Nodes[Nodes[index]->get_neighbour_id_top()]);
        }
        if(Nodes[index]->get_neighbour_id_left() != -1 && Nodes[Nodes[index]->get_neighbour_id_left()]->get_visited() == false)
        {
            setNodeWeight(Nodes[index]->get_neighbour_id_left(), index);
            OpenList.push_back(Nodes[Nodes[index]->get_neighbour_id_left()]);
        }
        if(Nodes[index]->get_neighbour_id_right() != -1 && Nodes[Nodes[index]->get_neighbour_id_right()]->get_visited() == false)
        {
            setNodeWeight(Nodes[index]->get_neighbour_id_right(), index);
            OpenList.push_back(Nodes[Nodes[index]->get_neighbour_id_right()]);
        }
        if(Nodes[index]->get_neighbour_id_below() != -1 && Nodes[Nodes[index]->get_neighbour_id_below()]->get_visited() == false)
        {
            setNodeWeight(Nodes[index]->get_neighbour_id_below(), index);
            OpenList.push_back(Nodes[Nodes[index]->get_neighbour_id_below()]);
        }
        OpenList.erase(OpenList.begin());
        if(OpenList.size() == 0)
        {
            /*for(int k=0; k<(int)Nodes.size(); k++)
            {
                std::cerr<<Nodes[k]->getID()<<" "<<Nodes[k]->get_neighbour_id_top()<<" "<<Nodes[k]->get_neighbour_id_left()<<" "<<Nodes[k]->get_neighbour_id_right()<<" "<<Nodes[k]->get_neighbour_id_below()<<std::endl;
            }
            createPath(startID, endID);*/
            return true;
        }
    }

}

void ClPathFinder::setNodeWeight(int nodeID, int parentID)
{
    Nodes[nodeID]->set_weight(Nodes[parentID]->get_weight() + 1);
    Nodes[nodeID]->set_visited(true);
}

void ClPathFinder::createPath(int startID, int endID)
{
    int nextNode, tempWeight;
    nextNode = startID;

    while (nextNode != endID)
    {
        tempWeight = Nodes[Nodes[nextNode]->get_neighbour_id_top()]->get_weight();
        nextNode = Nodes[nextNode]->get_neighbour_id_top();
        if(tempWeight > Nodes[Nodes[nextNode]->get_neighbour_id_left()]->get_weight())
        {
            tempWeight = Nodes[Nodes[nextNode]->get_neighbour_id_left()]->get_weight();
            nextNode = Nodes[nextNode]->get_neighbour_id_left();
        }
        if(tempWeight > Nodes[Nodes[nextNode]->get_neighbour_id_right()]->get_weight())
        {
            tempWeight = Nodes[Nodes[nextNode]->get_neighbour_id_right()]->get_weight();
            nextNode = Nodes[nextNode]->get_neighbour_id_right();
        }
        if(tempWeight > Nodes[Nodes[nextNode]->get_neighbour_id_below()]->get_weight())
        {
            tempWeight = Nodes[Nodes[nextNode]->get_neighbour_id_below()]->get_weight();
            nextNode = Nodes[nextNode]->get_neighbour_id_below();
        }
        Path.push_back(Nodes[nextNode]);
        if(nextNode == endID)
            break;
    }

}
void ClPathFinder::drawPath(sf::RenderWindow & window)
{
    for(int paint = 0; paint < (int)Path.size(); paint++)
    {
        sf::Vector2f position;
        position = Path[paint]->getPosition();
        sf::CircleShape Node;
        Node.setPosition(position);
        Node.setFillColor(sf::Color::Red);
        Node.setRadius(4.0f);
        window.draw(Node);
    }
}
