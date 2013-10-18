#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class ClNode
{
public:
    ClNode(const sf::Vector2f & position, int id);

    ~ClNode();

    void draw(sf::RenderWindow & window);
    int getID();
    void set_visited(bool visit);
    bool get_visited();
    void set_weight(int cost);
    int get_weight();
    void set_neighbour_id_top(int id);
    void set_neighbour_id_left(int id);
    void set_neighbour_id_right(int id);
    void set_neighbour_id_below(int id);
    int get_neighbour_id_top();
    int get_neighbour_id_left();
    int get_neighbour_id_right();
    int get_neighbour_id_below();
    float get_x_position();
    float get_y_position();
    sf::Vector2f getPosition() {return position;}


private:

    int id;
    sf::Vector2f position;
    bool visited;
    int weight;
    int neighbour_id_top;
    int neighbour_id_left;
    int neighbour_id_right;
    int neighbour_id_below;

};
#endif // NODE_HPP_INCLUDED
