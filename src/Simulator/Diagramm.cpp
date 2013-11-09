/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Patrick Senneka
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creates a diagramm which shows the number of casualties and threads over the time
---------------------------------------------------------------------------------------------------------------------------------------
*/
#include "../../include/Simulator/Diagramm.hpp"

ClDiagramm::ClDiagramm()
    {
    id=0;
    sf::Clock clock;
    font.loadFromFile("fonts/LiberationSerif-Regular.ttf");
    }

ClDiagramm::~ClDiagramm()
{
    //dtor
}

void ClDiagramm::registerBomb()
{
    EVENTTYPE type = BOMB;
    sf::Time time = clock.getElapsedTime();
    event bomb = {id, type, time};
    eventsVector.push_back(bomb);
    id++;
}

void ClDiagramm::registerFire()
{
    EVENTTYPE type = FIRE;
    sf::Time time = clock.getElapsedTime();
    event fire = {id, type, time};
    eventsVector.push_back(fire);
    id++;
}

void ClDiagramm::registerCasualties()
{
    EVENTTYPE type = CASUALTIES;
    sf::Time time = clock.getElapsedTime();
    event casualties = {id, type, time};
    eventsVector.push_back(casualties);
    id++;
}

void ClDiagramm::draw(const sf::Vector2f & position, float diagrammSizeX, float diagrammSizeY, sf::RenderWindow & window)
{
    this->position = position;
    //diagrammSizeX und diagrammSizeY define the size of the diagramm
    this->diagrammSizeX = diagrammSizeX - 2*OFFSET;
    this->diagrammSizeY = diagrammSizeY - 2*OFFSET;

    //in: Vector with events (BOMB,FIRE, CASUALTIES)
    //out: Graph which shows the events on a timescale and in y-direction the number of casualties

    //1. take last struct of eventsVector and calculate x-scale with time of the struct
    //2. loop through the eventsVector and count the number of CASUALTIES in each of 8 parts of the graph

    std::vector<event> fire;
    std::vector<event> bomb;
    sf::Vector2f tempSize;
    sf::Vector2f zeroPosition (position.x + OFFSET, position.y + diagrammSizeY + OFFSET);

    //sets each numberCasualties = 0
    int numberCasualties[NUMBERBLOCKS];
    for (int i=0; i<NUMBERBLOCKS; i++)
    {
        numberCasualties[i]=0;
    }
    if(eventsVector.size() != 0)
    {

    float timeLastEvent = eventsVector.back().time.asSeconds();
    for (int i=0; i<(int)eventsVector.size(); i++)
    {
        if(eventsVector[i].TYPE == CASUALTIES)
        {
            //numberCasualties is set for each block
            float tempTime = eventsVector[i].time.asSeconds();
            //check if the event is in the first of eight blocks on the x-axis
            for( int k = 0; k < NUMBERBLOCKS; k++)
            {
                if(tempTime >= (timeLastEvent/diagrammSizeX)*(k)*(diagrammSizeX/(float)NUMBERBLOCKS) && tempTime < (timeLastEvent/diagrammSizeX)*(k+1)*(diagrammSizeX/(float)NUMBERBLOCKS) )
                {
                    numberCasualties[k]++;
                }
            }
        }
        if(eventsVector[i].TYPE == FIRE)
        {
            fire.push_back(eventsVector[i]);
        }
        if(eventsVector[i].TYPE == BOMB)
        {
            bomb.push_back(eventsVector[i]);
        }
    }

    //draw fire
    if(fire.size() != 0)
    {

    int fireSize = fire.size();
    sf::RectangleShape fireRect[fireSize];
    tempSize.y = diagrammSizeY; //top of diagramm
    for (int j=0; j<(int)fire.size(); j++)
    {
        float fireTime = fire[j].time.asSeconds();
        tempSize.x = zeroPosition.x + (fireTime/timeLastEvent)*diagrammSizeX;
        fireRect[j].setPosition(tempSize.x, position.y + OFFSET );
        tempSize.x = 2;//weidth of the fireRect is 2
        fireRect[j].setSize(tempSize);
        fireRect[j].setFillColor(sf::Color::Red);
    }
    for(int j=0; j<(int)fire.size(); j++)
    {
        window.draw(fireRect[j]);
    }

    }


    //draw bomb
    if(bomb.size() != 0)
    {

    int bombSize = bomb.size();
    sf::RectangleShape bombRect[bombSize];
    tempSize.y = diagrammSizeY; //top of diagramm
    for (int j=0; j<(int)bomb.size(); j++)
    {
        float bombTime = bomb[j].time.asSeconds();
        tempSize.x = zeroPosition.x + (bombTime/timeLastEvent) * diagrammSizeX;
        bombRect[j].setPosition(tempSize.x, position.y + OFFSET );
        tempSize.x = 2;//weidth of the bombRect is 2
        bombRect[j].setSize(tempSize);
        bombRect[j].setFillColor(sf::Color::Yellow);
    }
    for(int j=0; j<(int)bomb.size(); j++)
    {
        window.draw(bombRect[j]);
    }

    }

    }

    drawBackground(window);

    drawXAxis(window);

    drawYAxis(window);


    //calculate maxNumberCasualties (number of the most casualties per block)
    float maxNumberCasualties=0.0;
    for (int i=0; i<NUMBERBLOCKS; i++)
    {
        if(maxNumberCasualties < numberCasualties[i])
        {
            maxNumberCasualties = numberCasualties[i];
        }
    }

    //draw rectangles for each block
    sf::RectangleShape block[NUMBERBLOCKS]; //there are 8 blocks


    tempSize.x = ((float)diagrammSizeX)/NUMBERBLOCKS;
    for(int i=0; i<NUMBERBLOCKS; i++)
    {
        block[i].setPosition( zeroPosition.x + (tempSize.x*i), zeroPosition.y-diagrammSizeY*(numberCasualties[i]/maxNumberCasualties) );
        tempSize.y = diagrammSizeY*(numberCasualties[i]/maxNumberCasualties); //height is set eacht time according to the numberCasualties of the block
        block[i].setSize(tempSize);
        block[i].setFillColor(sf::Color::Blue);
    }
    for(int i=0; i<NUMBERBLOCKS; i++)
    {
        window.draw(block[i]);
    }







    //draw axis legned
    sf::Text textAxisX;
    drawText(textAxisX, font, sf::Color::Black, 10, (position.x + diagrammSizeX + 1.5*OFFSET+5), (position.y + diagrammSizeY +OFFSET+1), sf::String("Time"), window);

    sf::Text textAxisY;
    drawText(textAxisY, font, sf::Color::Black, 10, (position.x + 0.5*OFFSET), (position.y + 0.3*OFFSET), sf::String("Casulties"), window);

    //draw legend
    sf::Text textLegend;
    drawText(textLegend, font, sf::Color::Black, 30, (position.x + 1*OFFSET), (position.y + diagrammSizeY+OFFSET +5), sf::String("Legende"), window);

    sf::Text textLegend1;
    drawText(textLegend1, font, sf::Color::Red, 30, (position.x + 4*OFFSET), (position.y + diagrammSizeY+OFFSET +5), sf::String("Fire |"), window);

    sf::Text textLegend2;
    drawText(textLegend2, font, sf::Color::Yellow, 30, (position.x + 6*OFFSET), (position.y + diagrammSizeY+OFFSET +5), sf::String("Bomb |"), window);

    //draw numberC (8)
    sf::Text textCasualties[NUMBERBLOCKS];

    for(int i=0; i<NUMBERBLOCKS; i++)
    {
        textCasualties[i].setFont(font);
        textCasualties[i].setColor(sf::Color::Black);
        textCasualties[i].setStyle(sf::Text::Regular);
        textCasualties[i].setCharacterSize(10);
        textCasualties[i].setPosition(position.x + 1.5*OFFSET+(i*(diagrammSizeX/(float)NUMBERBLOCKS)) , position.y + 0.5*OFFSET);

        std::stringstream number_ss;
        sf::String number;
        number_ss << numberCasualties[i];
        number = number_ss.str();

        textCasualties[i].setString(number);
        window.draw(textCasualties[i]);
    }
}

void ClDiagramm::drawBackground(sf::RenderWindow & window)
{
    //draw transparent background
        sf::RectangleShape background;
        sf::Vector2f backgroundSize (diagrammSizeX+ 2*OFFSET, diagrammSizeY+ 2*OFFSET);
        sf::Color backgroundColor;
        backgroundColor.r = backgroundColor.g = backgroundColor.b = 255;
        backgroundColor.a = 50;
        background.setPosition(position.x, position.y);
        background.setSize(backgroundSize);
        background.setFillColor(backgroundColor);

        window.draw(background);
}

void ClDiagramm::drawXAxis(sf::RenderWindow & window)
{
    //draw x-axis
        sf::Vertex xAxis[] =
        {
        sf::Vertex(sf::Vector2f(position.x + OFFSET, position.y + diagrammSizeY +OFFSET+1)),
        sf::Vertex(sf::Vector2f(position.x + diagrammSizeX + 1.5*OFFSET, position.y + diagrammSizeY +OFFSET+1))
        };
        sf::Vertex arrowX1[] =
        {
        sf::Vertex(sf::Vector2f(position.x + diagrammSizeX +1.5*OFFSET -8, position.y + diagrammSizeY +OFFSET+1 -8)),
        sf::Vertex(sf::Vector2f(position.x + diagrammSizeX + 1.5*OFFSET, position.y + diagrammSizeY +OFFSET+1))
        };
        sf::Vertex arrowX2[] =
        {
        sf::Vertex(sf::Vector2f(position.x + diagrammSizeX +1.5*OFFSET -8, position.y + diagrammSizeY +OFFSET+1 +8)),
        sf::Vertex(sf::Vector2f(position.x + diagrammSizeX + 1.5*OFFSET, position.y + diagrammSizeY +OFFSET+1))
        };

        window.draw(xAxis, 2, sf::Lines);
        window.draw(arrowX1, 2, sf::Lines);
        window.draw(arrowX2, 2, sf::Lines);
}
void ClDiagramm::drawYAxis(sf::RenderWindow & window)
{
        //draw y-axis
            sf::Vertex yAxis[] =
            {
            sf::Vertex(sf::Vector2f(position.x + OFFSET-1, position.y + 0.5*OFFSET)),
            sf::Vertex(sf::Vector2f(position.x + OFFSET-1, position.y + diagrammSizeY + OFFSET))
            };
            sf::Vertex arrowY1[] =
            {
            sf::Vertex(sf::Vector2f(position.x + OFFSET-1 -8, position.y + 0.5*OFFSET +8)),
            sf::Vertex(sf::Vector2f(position.x + OFFSET-1, position.y + 0.5*OFFSET))
            };
            sf::Vertex arrowY2[] =
            {
            sf::Vertex(sf::Vector2f(position.x + OFFSET-1 +8, position.y + 0.5*OFFSET +8)),
            sf::Vertex(sf::Vector2f(position.x + OFFSET-1, position.y + 0.5*OFFSET))
            };

            window.draw(yAxis, 2, sf::Lines);
            window.draw(arrowY1, 2, sf::Lines);
            window.draw(arrowY2, 2, sf::Lines);
}

void ClDiagramm::drawText(sf::Text dText, sf::Font dFont, sf::Color dColor, int characterSize, float dPositionX, float dPositionY, sf::String dString, sf::RenderWindow & window )
{
    dText.setFont(dFont);
    dText.setColor(dColor);
    dText.setStyle(sf::Text::Regular);
    dText.setCharacterSize(characterSize);
    dText.setPosition(dPositionX, dPositionY);
    dText.setString(dString);
    window.draw(dText);
}
