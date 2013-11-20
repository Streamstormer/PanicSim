/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Patrick Senneka
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    create an object, then call the function findPath(Vector2f, Vector2f) and you will recive an ClPath with the shortest Path
---------------------------------------------------------------------------------------------------------------------------------------
*/
#include "../../include/Simulator/PathFinder.hpp"

//creates all Nodes on creation of the PathFinder
ClPathFinder::ClPathFinder(ClArea *pArea, float nodeDistance, const sf::Vector2i & areaSize)
{
    nodeCounter = 0;
    this->pArea = pArea;
    this->nodeDistance = nodeDistance;
    this->areaSize = areaSize;
    createNodes();
}

//destructor deletes all Nodes. Paths are deleted in the individual crowds
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
//Support: Lukas and Patrick
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

    for(y = 0;y<=areaSize.y - nodeDistance; y+=nodeDistance)
    {
        for(x=0; x<=areaSize.x - nodeDistance; x+=nodeDistance)
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

    //2.
    int currentID;
    /*
    usefull functions of ClNode :
    void set_neighbour_id_top(int id);
    void set_neighbour_id_left(int id);
    void set_neighbour_id_right(int id);
    void set_neighbour_id_below(int id);
    */
    for(unsigned int n = 0; n<Nodes.size();  n++)
    {
        currentID = Nodes[n]->getID();
        // calculate ID left and right of current ID
        x = currentID % nodeNumber.x;
        y = (int)(currentID / nodeNumber.x);
        // left neighbour
        if(x>0 &&
           validID[(x-1)+y*nodeNumber.x]== true  &&
           ((x-1)+y*nodeNumber.x) < (int)Nodes.size() )
        {
            if( validConnection(currentID, ((x-1)+y*nodeNumber.x) ) == true)
            {
            Nodes[n]->set_neighbour_id_left((x-1)+y*nodeNumber.x);
            }
            else
            {
            Nodes[n]->set_neighbour_id_left(-1);
            }
        }
        // if the neigbour is not valid set it on -1
        else
        {
            Nodes[n]->set_neighbour_id_left(-1);
        }
        // right neighbour
        if((x < nodeNumber.x-1) && validID[(x+1)+y*nodeNumber.x]== true && ((x+1)+y*nodeNumber.x) < (int)Nodes.size() )
        {
            if(validConnection(currentID, ((x+1)+y*nodeNumber.x) ) == true)
            {
            Nodes[n]->set_neighbour_id_right((x+1)+y*nodeNumber.x);
            }
            else
            {
            Nodes[n]->set_neighbour_id_right(-1);
            }
        }
        else
        {
            Nodes[n]->set_neighbour_id_right(-1);
        }
        // top neighbour
        if(y>= 1 && validID[(x)+(y-1)*nodeNumber.x]== true && ((x)+(y-1)*nodeNumber.x) < (int)Nodes.size() )
        {
            if(validConnection(currentID, ((x)+(y-1)*nodeNumber.x) ) == true)
            {
            Nodes[n]->set_neighbour_id_top((x)+(y-1)*nodeNumber.x);
            }
            else
            {
            Nodes[n]->set_neighbour_id_top(-1);
            }
        }
        else
        {
            Nodes[n]->set_neighbour_id_top(-1);
        }
        // below neighbour
        if(y < nodeNumber.y&& validID[(x)+(y+1)*nodeNumber.x]== true && ((x)+(y+1)*nodeNumber.x) < (int)Nodes.size() )
        {
            if(validConnection(currentID, ((x)+(y+1)*nodeNumber.x) ) == true )
            {
            Nodes[n]->set_neighbour_id_below((x)+(y+1)*nodeNumber.x);
            }
            else
            {
            Nodes[n]->set_neighbour_id_below(-1);
            }
        }
        else
        {
            Nodes[n]->set_neighbour_id_below(-1);
        }
    }
}

// returns true if the connection is valid, which means that there is no static object between two nodes.
bool ClPathFinder::validConnection(int startNodeId, int endNodeId)
{
    return pArea->validPath(getNodeByID(startNodeId)->getPosition(), getNodeByID(endNodeId)->getPosition() );
}

/*
---------------------------------------------------------------------------------------------------------------------------------------
name:   tryToAddNode(const sf::Vector2i &here, int id)
---------------------------------------------------------------------------------------------------------------------------------------
return value: bool
---------------------------------------------------------------------------------------------------------------------------------------
The function validPoint of ClArea is used to check if the Vector is in a static object or not
---------------------------------------------------------------------------------------------------------------------------------------
*/
bool ClPathFinder::tryToAddNode(const sf::Vector2i &here, int id)
{
    ClNode *pAddMe;
    if(pArea->isInvalidNode(sf::Vector2f(here.x, here.y),nodeDistance)== false)
    {
        pAddMe = new ClNode(sf::Vector2f(here.x,here.y), id);
        Nodes.push_back(pAddMe);
        return true;
    }
    return false;
}

/*
---------------------------------------------------------------------------------------------------------------------------------------
name:   findPath(int startID, int endID)
---------------------------------------------------------------------------------------------------------------------------------------
return value:   true if Path can be found       false if no Path exists
---------------------------------------------------------------------------------------------------------------------------------------
The Node with the endID is set a weight of 0. Depending on the walkable distance between Nodes to the Node with the endID their
weights are assigned
---------------------------------------------------------------------------------------------------------------------------------------
*/
bool ClPathFinder::findPath(int startID, int endID, ClPath *Path)
{
    //the node weight and the visited state have to be reseted for creating a new path
    for(int k=0; k<(int)Nodes.size(); k++)
    {
        Nodes[k]->set_weight(INFINITY);
        Nodes[k]->set_visited(false);
    }
    if(startID == endID)
        return false;
    else
    {
        //the end node is assigned the weight 0
        getNodeByID(endID)->set_visited(true);
        getNodeByID(endID)->set_weight(0);
        OpenList.push_back(getNodeByID(endID));
    }
    while(OpenList.size() > 0)
    {
        //if the neighbour-nodes exist and they are not visited they are assigned a weight (parentweight + 1)
        int index = OpenList[0]->getID();

        if ( getNodeByID(index)->get_neighbour_id_top() != -1 )
        {
            tryToAddNeighbour(index, getNodeByID(index)->get_neighbour_id_top(), getNodeByID(getNodeByID(index)->get_neighbour_id_top())->get_visited() );
        }
        if ( getNodeByID(index)->get_neighbour_id_left() != -1)
        {
            tryToAddNeighbour(index, getNodeByID(index)->get_neighbour_id_left(), getNodeByID(getNodeByID(index)->get_neighbour_id_left())->get_visited() );
        }
        if ( getNodeByID(index)->get_neighbour_id_right() != -1)
        {
            tryToAddNeighbour(index, getNodeByID(index)->get_neighbour_id_right(), getNodeByID(getNodeByID(index)->get_neighbour_id_right())->get_visited() );
        }
        if ( getNodeByID(index)->get_neighbour_id_below() != -1)
        {
            tryToAddNeighbour(index, getNodeByID(index)->get_neighbour_id_below(), getNodeByID(getNodeByID(index)->get_neighbour_id_below())->get_visited() );
        }

        OpenList.erase(OpenList.begin());
        if(OpenList.size() == 0)
        {
            createPath(startID, endID, Path);
            return true;
        }
    }
    return false;

}
// helper-fuction to assign node-weight. the function must not be called without checking if the node exists
void ClPathFinder::tryToAddNeighbour(int index, int neighbour_id, bool visited)
{
    if(visited == false)
        {
            setNodeWeight(neighbour_id, index);
            OpenList.push_back(getNodeByID(neighbour_id));
        }
}

/*
---------------------------------------------------------------------------------------------------------------------------------------
name:   setNodeWeight(int nodeID, int parentID)
---------------------------------------------------------------------------------------------------------------------------------------
return value:   none
---------------------------------------------------------------------------------------------------------------------------------------
setNodeWeight assigns the Node weight depending on the parents Node weight.
---------------------------------------------------------------------------------------------------------------------------------------
*/
void ClPathFinder::setNodeWeight(int nodeID, int parentID)
{
    int tempParentWeight = getNodeByID(parentID)->get_weight();
    getNodeByID(nodeID)->set_weight(tempParentWeight + 1);
    getNodeByID(nodeID)->set_visited(true);
}

/*
---------------------------------------------------------------------------------------------------------------------------------------
name:   createPath(int startID, int endID)
---------------------------------------------------------------------------------------------------------------------------------------
return value:   ture if a path from startID to endID can be found           false if there is no path
---------------------------------------------------------------------------------------------------------------------------------------
createPath starts at the Node with the startID and takes always the neighbour with the lowest weight as the the next Node
until the Node with the endID is reached.
---------------------------------------------------------------------------------------------------------------------------------------
*/
bool ClPathFinder::createPath(int startID, int endID, ClPath *Path)
{
    int nextNode, tempNext;
    int tempWeight = 32000;
    int counter = 0;
    nextNode = startID;
    tempNext = startID;

    while (nextNode != endID)
    {
        counter ++;
        //the if-else does not prefer a hozontal or vertical path
        if(counter%2)
        {
            if(getNodeByID(nextNode)->get_neighbour_id_left() != -1)
            {
                getTempNextNode(getNodeByID(nextNode)->get_neighbour_id_left(), & tempWeight, & tempNext);
            }
            if(getNodeByID(nextNode)->get_neighbour_id_right() != -1)
            {
                getTempNextNode(getNodeByID(nextNode)->get_neighbour_id_right(), & tempWeight, & tempNext);
            }
            if(getNodeByID(nextNode)->get_neighbour_id_below() != -1)
            {
                getTempNextNode(getNodeByID(nextNode)->get_neighbour_id_below(), & tempWeight, & tempNext);
            }
            if(getNodeByID(nextNode)->get_neighbour_id_top() != -1)
            {
                getTempNextNode(getNodeByID(nextNode)->get_neighbour_id_top(), & tempWeight, & tempNext);
            }
        }
        else
        {
            if(getNodeByID(nextNode)->get_neighbour_id_below() != -1)
            {
                getTempNextNode(getNodeByID(nextNode)->get_neighbour_id_below(), & tempWeight, & tempNext);
            }
            if(getNodeByID(nextNode)->get_neighbour_id_top() != -1)
            {
                getTempNextNode(getNodeByID(nextNode)->get_neighbour_id_top(), & tempWeight, & tempNext);
            }
            if(getNodeByID(nextNode)->get_neighbour_id_left() != -1)
            {
                getTempNextNode(getNodeByID(nextNode)->get_neighbour_id_left(), & tempWeight, & tempNext);
            }
            if(getNodeByID(nextNode)->get_neighbour_id_right() != -1)
            {
                getTempNextNode(getNodeByID(nextNode)->get_neighbour_id_right(), & tempWeight, & tempNext);
            }
        }

        Path->addVector(getNodeByID(nextNode)->getPosition());
        nextNode = tempNext;
        if(nextNode == endID)
        {
            Path->addVector(getNodeByID(nextNode)->getPosition());
            return true;
        }
        if(counter > (int)Nodes.size())
        {
            return false;
        }
    }
    return false;
}
//helper-function to assign the tempNextNode if the tempWeight is smaller
void ClPathFinder::getTempNextNode (int neighbourId, int *pTempWeight, int *pTempNextNode)
{
    if(*pTempWeight > getNodeByID(neighbourId)->get_weight() )
    {
        *pTempWeight = getNodeByID(neighbourId)->get_weight();
        *pTempNextNode = neighbourId;
    }
}
/*
---------------------------------------------------------------------------------------------------------------------------------------
name:   getNodeByID(int id)
---------------------------------------------------------------------------------------------------------------------------------------
return value:   ClNode* with the id
---------------------------------------------------------------------------------------------------------------------------------------
helper-function to allow a fast addressing of the right Node (so not the whole Vector Nodes has to be walked
---------------------------------------------------------------------------------------------------------------------------------------
*/
ClNode* ClPathFinder::getNodeByID(int id)
{
    int n = id;
    if( n >= (int)Nodes.size())
    {
        n = Nodes.size()-1;
    }
    for ( ; n>=0; n--)
    {
        if (Nodes[n]->getID() == id)
        {
            return Nodes[n];
        }
    }
    return NULL;
}

/*
---------------------------------------------------------------------------------------------------------------------------------------
name:   assignVectorNode(const sf::Vector2f & Position)
---------------------------------------------------------------------------------------------------------------------------------------
return value:   id of the nearest Node
---------------------------------------------------------------------------------------------------------------------------------------
helper-function for an easy use of the pathFinder
A Path can be created without knowing about the Nodes, because the Position is assigned to the nearest Node
The function is called rarely so that a fast implementation was not nessesary
---------------------------------------------------------------------------------------------------------------------------------------
*/
int ClPathFinder::assignVectorNode(const sf::Vector2f & Position)
{
    int id = -1;
    double distance = 1000000000;
    double test;

    for (int n=0; n < (int)Nodes.size(); n++)
    {
        test = ( ((Nodes[n]->get_x_position() - Position.x)*(Nodes[n]->get_x_position() - Position.x)) + ((Nodes[n]->get_y_position() - Position.y)*(Nodes[n]->get_y_position() - Position.y)) );
        if(test < distance)
        {
            distance = test;
            id = Nodes[n]->getID();
        }
    }

    return id;
}

/*
---------------------------------------------------------------------------------------------------------------------------------------
name:   findPath(const sf::Vector2f & Start, const sf::Vector2f & Ende)
---------------------------------------------------------------------------------------------------------------------------------------
return value:   pointer to ClPath object    object size is 0 if there is no path        objectsize is >1 if there is a path
---------------------------------------------------------------------------------------------------------------------------------------
helper-function to address the private findPath function with the right id's
A Path is created, which stores the path steps as vectors
---------------------------------------------------------------------------------------------------------------------------------------
*/
ClPath* ClPathFinder::findPath(const sf::Vector2f & Start, const sf::Vector2f & Ende)
{
    bool temp;
    ClPath *pPath = new ClPath(Start);

    int startID = assignVectorNode(Start);
    int endID = assignVectorNode(Ende);

    if (startID == -1 || endID == -1)
    {
        return NULL;
    }

    temp = findPath(startID, endID , pPath );
    if(temp == true)
    {
        pPath->addVector(Ende);
        return pPath;
    }
    else
    {
        pPath->clearVectorPath();
        return pPath;
    }
}


/*
---------------------------------------------------------------------------------------------------------------------------------------
name:   draw(sf::RenderWindow & window)
---------------------------------------------------------------------------------------------------------------------------------------
return value:   none
---------------------------------------------------------------------------------------------------------------------------------------
draw(sf::RenderWindow & window) is a test-function to validate if the createNodes() works properly
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

