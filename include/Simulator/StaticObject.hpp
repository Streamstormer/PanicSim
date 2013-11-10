#ifndef C_STATIC_OBJECT_INCLUDE
#define C_STATIC_OBJECT_INCLUDE

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

enum staticObjects{STAGE, BAR, WC, WALL, FENCE, GATE};
const unsigned int MAXSTATICOBJECTTYPES = GATE; // set this enum to the rightmost of all staticObjects

class ClStaticObject
{
public:
    ClStaticObject(sf::RectangleShape *Rectconst, int id, enum staticObjects Type,const sf::Texture &texture_fire);
    ~ClStaticObject();
    void draw(sf::RenderWindow& window);
    const sf::Vector2f &getCenter();
    bool Intersects( const sf::Vector2f  &Position); // returns true if Position is inside of the StaticObject
    bool IntersectsRectangle(sf::Rect<float> &testRect);
    int getID();
    enum staticObjects getType();
    const sf::Vector2f &getPosition();
    const sf::Vector2f &getSize();
    bool getIsOnFire();

    float getRotation();
    void startToBurn();
    void setPosition(const sf::Vector2f &position);
    void setRotation(float rotation);
    void setSize(const sf::Vector2f &newSize);
    bool isValidPath(sf::Vector2f startPoint, sf::Vector2f endPoint); //used for pathfinding. returns true if there is a static object in the path
    sf::Vector2f getMiddleOfLine();
    bool getIsChecked();
    void setIsChecked(bool check);
    sf::Rect<float> &biggerRect(); // makes the Rect bigger and gives it too Area
private:
    void getTextfromType(int type);
    void settext();

    enum staticObjects Type;
    sf::RectangleShape *Rect;
    int id; // unique id
    sf::Text text;
    sf::Font font;
    sf::RectangleShape line;
     sf::Rect<int> subrectFire;
    sf::Sprite fire_sprite;
    sf::Clock fire_clock;
    void subrecttoNumber(int number);
    int bildID;
    bool isOnFire;
    const static int PICTUREDURATION =50;
    const static int ANIMATIONSQUARE =8;
    bool isChecked;
    sf::Rect<float> bigRect;

};

#endif // C_STATIC_OBJECT_INCLUDE
