/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Patrick Senneka
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    Path stores the Nodes of the shortest Path in the right order.
---------------------------------------------------------------------------------------------------------------------------------------
*/
#ifndef PATH_HPP_INCLUDED
#define PATH_HPP_INCLUDED
#include "Node.hpp"

#include <SFML/Graphics.hpp>

class ClPath
{
public:
    ClPath(const sf::Vector2f & startVector);
    ~ClPath();

    sf::Vector2f getNextVector();
    void addVector(const sf::Vector2f & add);
    int getSize();
    void clearVectorPath ();

    //test-function
    void drawPath(sf::RenderWindow & window);

private:
    int position;
    std::vector<sf::Vector2f> vectorPath;

};
#endif // PATH_HPP_INCLUDED
