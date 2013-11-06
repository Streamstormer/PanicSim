#include "../../include/Simulator/StaticObject.hpp"
#include <math.h>

ClStaticObject::ClStaticObject(sf::RectangleShape *Rectconst, int id, enum staticObjects Type)
{
    Rect = Rectconst;
    this->Type = Type;

    this->id = id;

    Rect->setOrigin(Rect->getSize().x/2,Rect->getSize().y/2);
    text.setPosition(Rect->getPosition().x,Rect->getPosition().y);
    getTextfromType(Type);
    font.loadFromFile("fonts/LiberationSerif-Regular.ttf");
    text.setFont(font);
    text.setCharacterSize(60);
    text.setColor(sf::Color::Black);


    text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height);

    if(Rect->getRotation()>90 && Rect->getRotation()<271)
        {
        text.setRotation(Rect->getRotation()-180);
        }
        else
        {
            text.setRotation(Rect->getRotation());
        }

    while((Rect->getSize().x<text.getLocalBounds().width || Rect->getSize().y< text.getLocalBounds().height) && text.getCharacterSize()> 30)
    {
            text.setCharacterSize(text.getCharacterSize()-1);
            text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height);

    }

    if(Type!=FENCE && Type!=WALL)
    {
        line.setSize(sf::Vector2f(Rect->getSize().x,3));
        line.setFillColor(sf::Color::Red);
        line.setPosition(Rect->getPosition());
        line.setOrigin(Rect->getSize().x/2,-Rect->getSize().y/2+line.getSize().y);
        line.setRotation(Rect->getRotation());
    }



}
enum staticObjects ClStaticObject::getType()
{
    return Type;
}

ClStaticObject::~ClStaticObject()
{
    delete Rect;
}

void ClStaticObject::draw(sf::RenderWindow& window)
{

    window.draw(*Rect);

    window.draw(line);
    window.draw(text);

}
bool ClStaticObject::Intersects( const sf::Vector2f  &Position)
    {
        return Rect->getGlobalBounds().contains(Position);
    }
    int ClStaticObject::getID()
    {
        return id;
    }
    const sf::Vector2f &ClStaticObject::getPosition()
    {
        return Rect->getPosition();
    }
    const sf::Vector2f &ClStaticObject::getSize()
    {
        return Rect->getSize();
    }

    float ClStaticObject::getRotation()
    {
        return Rect->getRotation();
    }

    void ClStaticObject::setPosition(const sf::Vector2f &position)
    {
        Rect->setPosition(position);
        settext();
    }
    void ClStaticObject::setRotation(float rotation)
    {
        Rect->setRotation(rotation);
        settext();
    }
    void ClStaticObject::setSize(const sf::Vector2f &newSize)
    {
        Rect->setSize(newSize);
        settext();
    }

    void ClStaticObject::getTextfromType(int type)
    {
      switch(type)
        {
        case STAGE:
            text.setString(L"Bühne");
            break;
        case BAR:
            text.setString("Bar");
            break;
        case WC:
            text.setString("WC");
            break;
        case WALL:
            text.setString("Mauer");
            break;
        case FENCE:
            text.setString("Zaun");
            break;
        case GATE:
            text.setString("Ausgang");
            break;
        }
    }

   const sf::Vector2f & ClStaticObject::getCenter()
   {
      return Rect->getPosition();
   }

   void ClStaticObject::settext()
   {
    Rect->setOrigin(Rect->getSize().x/2,Rect->getSize().y/2);
    text.setPosition(Rect->getPosition().x,Rect->getPosition().y);
    text.setCharacterSize(60);

    /*
    getTextfromType(Type);
    font.loadFromFile("fonts/LiberationSerif-Regular.ttf");
    text.setFont(font);


    text.setColor(sf::Color::Black);
*/

    text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height);

    if(Rect->getRotation()>90 && Rect->getRotation()<271)
        {
        text.setRotation(Rect->getRotation()-180);
        }
        else
        {
            text.setRotation(Rect->getRotation());
        }

    while((Rect->getSize().x<text.getLocalBounds().width || Rect->getSize().y< text.getLocalBounds().height) && text.getCharacterSize()> 30)
    {
            text.setCharacterSize(text.getCharacterSize()-1);
            text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height);

    }

    if(Type!=FENCE && Type!=WALL)
    {
        line.setSize(sf::Vector2f(Rect->getSize().x,3));
        line.setFillColor(sf::Color::Red);
        line.setPosition(Rect->getPosition());
        line.setOrigin(Rect->getSize().x/2,-Rect->getSize().y/2+line.getSize().y);
        line.setRotation(Rect->getRotation());
    }
   }

bool ClStaticObject::isValidPath(sf::Vector2f startPoint, sf::Vector2f endPoint)
{
    if(Type==GATE) return false; // no collision with EXITS / GATES
    sf::Rect<float> testRect;
    //checks if start node and end node are horizontal or vertical
    if(startPoint.y == endPoint.y)
    {
    if(startPoint.x < endPoint.x)
    {
        testRect.left = startPoint.x;
    }
    else
    {
        testRect.left = endPoint.x;
    }

    testRect.top = startPoint.y;

    testRect.width = abs(startPoint.x-endPoint.x);
    testRect.height = 1;
    return Rect->getGlobalBounds().intersects(testRect);
    }

    //creates rect between start and end point. returns true if there is a intersect with another object
    if(startPoint.y < endPoint.y)
    {
        testRect.top = startPoint.y;
    }
    else
    {
        testRect.top = endPoint.y;
    }

    testRect.left = startPoint.x;

    testRect.height = abs(startPoint.y-endPoint.y);
    testRect.width = 1;
    return Rect->getGlobalBounds().intersects(testRect);
}

sf::Vector2f ClStaticObject::getMiddleOfLine()
{
    return sf::Vector2f(line.getGlobalBounds().left + (line.getGlobalBounds().width / 2), line.getGlobalBounds().top + (line.getGlobalBounds().height / 2));
}
