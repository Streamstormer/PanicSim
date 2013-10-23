#include <SFML/Graphics.hpp>
#ifndef C_STATIC_OBJECT_INCLUDE
#define C_STATIC_OBJECT_INCLUDE

#include <iostream>
#include <math.h>

enum staticObjects{STAGE, BAR, WC, WALL, FENCE};
const unsigned int MAXSTATICOBJECTTYPES = FENCE; // set this enum to the rightmost of all staticObjects

class ClStaticObject
{
public:
    ClStaticObject(sf::RectangleShape *Rectconst, int id, int Type);
    ~ClStaticObject();
    void draw(sf::RenderWindow& window);
    sf::Vector2f getCenter();
    bool Intersects( const sf::Vector2f  &Position); // returns true if Position is inside of the StaticObject
    int getID();
    int getType();
    const sf::Vector2f &getPosition();
    const sf::Vector2f &getSize();

    float getRotation();

    void setPosition(const sf::Vector2f &position);
    void setRotation(float rotation);
    void setSize(const sf::Vector2f &newSize);

private:
    void getTextfromType(int type);


    int Type;
    sf::RectangleShape *Rect;
    int id; // unique id
    sf::Text text;
    sf::Font font;


};

#endif // C_STATIC_OBJECT_INCLUDE
