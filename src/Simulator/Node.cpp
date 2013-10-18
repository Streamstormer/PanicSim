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

void ClNode::draw(sf::RenderWindow& window)
    {
        sf::CircleShape Node;
        Node.setPosition(position);
        Node.setFillColor(sf::Color::Cyan);
        Node.setRadius(1.0f);
        window.draw(Node);

    }

void ClNode::set_visited(bool visit)
{
    this->visited = visit;
}
bool ClNode::get_visited()
{
    return visited;
}

void ClNode::set_weight(int cost)
{
    this->weight = weight;
}
int ClNode::get_weight()
{
    return weight;
}

void ClNode::set_neighbour_id_top(int id)
{
    this->neighbour_id_top = id;
}
void ClNode::set_neighbour_id_left(int id)
{
    this->neighbour_id_left = id;
}
void ClNode::set_neighbour_id_right(int id)
{
    this->neighbour_id_right = id;
}
void ClNode::set_neighbour_id_below(int id)
{
    this->neighbour_id_below = id;
}
int ClNode::getID()
{
    return id;
}
int ClNode::get_neighbour_id_top()
{
    return neighbour_id_top;
}
int ClNode::get_neighbour_id_left()
{
    return neighbour_id_left;
}
int ClNode::get_neighbour_id_right()
{
    return neighbour_id_right;
}
int ClNode::get_neighbour_id_below()
{
    return neighbour_id_below;
}
float ClNode::get_x_position()
{
    return position.x;
}
float ClNode::get_y_position()
{
    return position.y;
}
