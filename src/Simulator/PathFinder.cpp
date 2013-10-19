#include "../../include/Simulator/PathFinder.hpp"

ClPathFinder::ClPathFinder(ClArea *pArea, float nodeDistance, const sf::Vector2f & areaSize)
{
    this->pArea = pArea;
    this->nodeDistance = nodeDistance;
    this->areaSize = areaSize;
    createNodes();
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
    // 1. create Nodes and check wheather the nodes are valid
    // 1. create a list of valid nodes based on pArea->isValidPoint
    // 2. add neighbour ids based on this list
    sf::Vector2f testPos;
    sf::Vector2i nodeNumber((int)(areaSize.y/nodeDistance), (int)(areaSize.x/nodeDistance));
    int idCounter=0;
    int x, y;
    bool validID[nodeNumber.x*nodeNumber.y]; // enough memory to store wheather it is a valid id or not

    for(y = 0;y<areaSize.y; y+=nodeDistance)
    {
        for(x=0; x<areaSize.x; x+=nodeDistance)
        {
            //1.
            validID[idCounter] = false;
            if(tryToAddNode(sf::Vector2i(x,y),idCounter))
            {
                validID[idCounter] = true;
            }
            idCounter++; // set idCounter ++ even if there is no node to add
        }
    }
    // debug output of validID Array
    /*
    for (int i = 0; i < nodeNumber.x * nodeNumber.y; i++)
    {
        if(i % nodeNumber.x == 0)
        {
                std::cerr << std::endl;
        }
        std::cerr << i << " " << validID[i] << " ";
    } */
    //2.
    int currentID;
    /*
    usefull functions :
    void set_neighbour_id_top(int id);
    void set_neighbour_id_left(int id);
    void set_neighbour_id_right(int id);
    void set_neighbour_id_below(int id);
    */
    for(unsigned int n = 0; n<Nodes.size(); n++)
    {
        currentID = Nodes[n]->getID();
        // calculate ID left and right of current ID
        x = currentID % nodeNumber.x;
        y = (int)(currentID / nodeNumber.x);
        std::cerr << "curID :" << currentID;
        //left neighbour
        if ( x > 0 )
        if( validID[(x-1)+y*nodeNumber.x]== true)
        {
            Nodes[n]->set_neighbour_id_left((x-1)+y*nodeNumber.x);
            std::cerr << "left :" << (x-1)+y*nodeNumber.x;
        }
        else
        {
            Nodes[n]->set_neighbour_id_left(-1);
        }
        // right neighbour
        if((x < nodeNumber.x-1) && validID[(x+1)+y*nodeNumber.x]== true )
        {
            Nodes[n]->set_neighbour_id_right((x+1)+y*nodeNumber.x);
            std::cerr << "right :" << (x+1)+y*nodeNumber.x;
        }
        else
        {
            Nodes[n]->set_neighbour_id_right(-1);
        }
        // top neighbour
        if(y >= 1)
        if(validID[(x)+(y-1)*nodeNumber.x]== true )
        {
            Nodes[n]->set_neighbour_id_top((x)+(y-1)*nodeNumber.x);
            std::cerr << "top :" << (x)+(y-1)*nodeNumber.x;
        }
        else
        {
            Nodes[n]->set_neighbour_id_top(-1);
        }
        // bottom neighbour
        if(y < nodeNumber.y&& validID[(x)+(y+1)*nodeNumber.x]== true )
        {
            Nodes[n]->set_neighbour_id_below((x)+(y+1)*nodeNumber.x);
            std::cerr << "bottom :" << (x)+(y+1)*nodeNumber.x;
        }
        else
        {
            Nodes[n]->set_neighbour_id_below(-1);
        }
       if(n>= 30 && n <= 40) std::cerr << std::endl;
    }

    std::cerr << "idCounter :"<< idCounter;

}

bool ClPathFinder::tryToAddNode(const sf::Vector2i &here, int id)
{
    int tempX = (int)here.x/nodeDistance;
    int tempY = (int)here.y/nodeDistance;
    ClNode *pAddMe;
    if(pArea->validPoint(sf::Vector2f(here.x, here.y)))
    {
        pAddMe = new ClNode(sf::Vector2f(here.x,here.y), id);
        Nodes.push_back(pAddMe);
        return true;
    }
    return false;
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
