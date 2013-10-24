/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Patrick Senneka
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    Nodes are used for the pathfinding.
---------------------------------------------------------------------------------------------------------------------------------------
*/
#include "../../include/Simulator/Node.hpp"

ClNode::ClNode(const sf::Vector2f & position, int id)
    {
        this->position = position;
        this->id = id;
        this->visited = false;
    }

ClNode::~ClNode()
{
    //dtor
}

//draws the Node on the screen
void ClNode::draw(sf::RenderWindow& window)
    {
        sf::CircleShape Node;
        Node.setPosition(position);
        Node.setFillColor(sf::Color::Cyan);
        Node.setRadius(1.0f);
        window.draw(Node);

    }

//Node can be set on visited
void ClNode::set_visited(bool visit)
{
    this->visited = visit;
}

//Nodes status of visited is replied
bool ClNode::get_visited()
{
    return visited;
}

//wight of the Node can be set
void ClNode::set_weight(int cost)
{
    this->weight = cost;
}

//Nodes weight is returned
int ClNode::get_weight()
{
    return weight;
}

//Nodes top-neighbour can be set
void ClNode::set_neighbour_id_top(int id)
{
    this->neighbour_id_top = id;
}

//Nodes left-neighbour can be set
void ClNode::set_neighbour_id_left(int id)
{
    this->neighbour_id_left = id;
}

//Nodes right-neighbour can be set
void ClNode::set_neighbour_id_right(int id)
{
    this->neighbour_id_right = id;
}

//Nodes below-neighbour can be set
void ClNode::set_neighbour_id_below(int id)
{
    this->neighbour_id_below = id;
}

//Id will be returned
int ClNode::getID()
{
    return id;
}

//id of top-neighbour will be returned
int ClNode::get_neighbour_id_top()
{
    return neighbour_id_top;
}

//id of left-neighbour will be returned
int ClNode::get_neighbour_id_left()
{
    return neighbour_id_left;
}

//id of right-neighbour will be returned
int ClNode::get_neighbour_id_right()
{
    return neighbour_id_right;
}

//id of below-neighbour will be returned
int ClNode::get_neighbour_id_below()
{
    return neighbour_id_below;
}

//position in x direction will be returned
float ClNode::get_x_position()
{
    return position.x;
}

//position in y direction will be returned
float ClNode::get_y_position()
{
    return position.y;
}
