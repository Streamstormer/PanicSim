#include "../../include/Simulator/StaticObject.hpp"
#include <math.h>

ClStaticObject::ClStaticObject(sf::RectangleShape *Rectconst, int id, enum staticObjects Type,const sf::Texture &texture_fire)
{
    Rect = Rectconst;
    this->Type = Type;

    this->id = id;
    firstTime = false;

    Rect->setOrigin(Rect->getSize().x/2,Rect->getSize().y/2);  // sets the point where the Rect will be rotatet into the middle
    text.setPosition(Rect->getPosition().x,Rect->getPosition().y); //sets Position of the Static Object
    getTextfromType(Type);                                          //sets Text on the Object
    font.loadFromFile("fonts/LiberationSerif-Regular.ttf");         //loads the font
    text.setFont(font);
    text.setCharacterSize(60);
    text.setColor(sf::Color::Black);

    isChecked = false;                                  // is used to expand the fire


    text.setOrigin(text.getLocalBounds().width/2,text.getLocalBounds().height); // sets the text on the middle of the Object

    if(Rect->getRotation()>90 && Rect->getRotation()<271)       //Proofes that the text
        {
        text.setRotation(Rect->getRotation()-180);
        }
        else
        {
            text.setRotation(Rect->getRotation());
        }

    while((Rect->getSize().x<text.getLocalBounds().width || Rect->getSize().y< text.getLocalBounds().height) && text.getCharacterSize()> 30)
    {
        // if the Size of the Static Object is smaller than the Text, the text size will be minimized
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
        //draws a red line, where the front of the Object is
    }


    fire_sprite.setTexture(texture_fire);
    subrectFire.top=0;
    subrectFire.left=0;
    subrectFire.width=texture_fire.getSize().x/8;
    subrectFire.height=texture_fire.getSize().y/8;
    isOnFire = false;
    bildID=0;


}

void ClStaticObject::subrecttoNumber(int number)
{
    //calculates the picture wich is used for the fire
    subrectFire.top = (int)(number/ANIMATIONSQUARE)*subrectFire.height;
    subrectFire.left = (int)(number%ANIMATIONSQUARE)*subrectFire.width;
     fire_sprite.setTextureRect(subrectFire);

}

 void ClStaticObject::startToBurn()
 {
      isOnFire=true;
      firstTime=true;
      fire_clock.restart();
 }
bool ClStaticObject::getIsOnFire()
{
    if (firstTime== true)
    {
        return false;
    }
    return isOnFire;

}

bool ClStaticObject::getIsChecked()
{
    return isChecked;
}

void ClStaticObject::setIsChecked(bool check)
{
    isChecked = check;
}

sf::Rect<float> &ClStaticObject::biggerRect()
{
    bigRect= Rect->getGlobalBounds();  // checks if there are Object near the actual one and let them burn
    bigRect.top= bigRect.top-100;
    bigRect.left= bigRect.left-100;
    bigRect.width= bigRect.width+ 2*100;
    bigRect.height= bigRect.height+ 2*100;

    return bigRect;

}
bool ClStaticObject::IntersectsRectangle(sf::Rect<float> &testRect)
{
     return this->Rect->getGlobalBounds().intersects(testRect);
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

     if (isOnFire)
    {

            // 1. calculate picture number from time
        // 2. chose correct picture

        int time =fire_clock.getElapsedTime().asMilliseconds();
        bildID = (int)time/PICTUREDURATION;
        if (bildID >62)
        {
            fire_clock.restart();
            bildID = 0;
        }
        subrecttoNumber(bildID);
        int countFire=0;

        if(Rect->getSize().x > Rect->getSize().y)  //looks for close neighbours and sets them to fire
        {
            countFire = (Rect->getSize().x-100)/128;//    /128
            if(countFire==0)
            {
                fire_sprite.setPosition(Rect->getPosition());
                fire_sprite.setOrigin(subrectFire.width/2,subrectFire.height*2/3);
                window.draw(fire_sprite);
            }
            else
            {
                int i=0;
                if (Rect->getRotation()==0 ||Rect->getRotation() == 180 || Rect->getRotation() == 360)
                {
                    while (i<countFire)
                    {
                        fire_sprite.setPosition(Rect->getGlobalBounds().left+(i*128+100),Rect->getGlobalBounds().top+Rect->getSize().y/2);
                        fire_sprite.setOrigin(subrectFire.width/2,subrectFire.height*2/3);
                        window.draw(fire_sprite);
                        i++;
                    }
                }

                if (Rect->getRotation()==90|| Rect->getRotation()==270)
                {
                   while (i<countFire)
                    {
                        fire_sprite.setPosition(Rect->getGlobalBounds().left+Rect->getSize().y/2,Rect->getGlobalBounds().top+(i*128+100));
                        fire_sprite.setOrigin(subrectFire.width/2,subrectFire.height*2/3);
                        window.draw(fire_sprite);
                        i++;
                    }
                }


            }
        }
        else
        {
            countFire = Rect->getSize().y/128;
            if(countFire==0)
            {
            fire_sprite.setPosition(Rect->getPosition());
            fire_sprite.setOrigin(subrectFire.width/2,subrectFire.height*2/3);
            window.draw(fire_sprite);
            }
            else
            {
            int i=0;
                if (Rect->getRotation()==0 ||Rect->getRotation() == 180 || Rect->getRotation() == 360)
                {
                    while (i<countFire)
                    {
                        fire_sprite.setPosition(Rect->getGlobalBounds().left+Rect->getSize().x/2,Rect->getGlobalBounds().top+(i*128+100));
                        fire_sprite.setOrigin(subrectFire.width/2,subrectFire.height*2/3);
                        window.draw(fire_sprite);
                        i++;
                    }
                }
                if (Rect->getRotation()==90|| Rect->getRotation()==270)
                {
                   while (i<countFire)
                    {
                        fire_sprite.setPosition(Rect->getGlobalBounds().left+(i*128+100),Rect->getGlobalBounds().top+Rect->getSize().x/2);
                        fire_sprite.setOrigin(subrectFire.width/2,subrectFire.height*2/3);
                        window.draw(fire_sprite);
                        i++;
                    }
            }
        }

    }
    }
}


bool ClStaticObject::getfirstTime()
{
    return firstTime;
}
void ClStaticObject::setfirstTime(bool check)
{
    firstTime= check;
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

    if(Type!=FENCE && Type!=WALL && Type != GATE)
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
    if(Type==FENCE) return false; //isValidPath is only called in State Panik --> there FENCE is no collision
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
