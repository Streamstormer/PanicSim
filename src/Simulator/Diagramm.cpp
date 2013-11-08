/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Patrick Senneka
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    creates a diagramm which shows the number of casualties and threads over the time
---------------------------------------------------------------------------------------------------------------------------------------
*/
#include "../../include/Simulator/Diagramm.hpp"

ClDiagramm::ClDiagramm(const sf::Vector2f & position, float diagrammSizeX, float diagrammSizeY)
    {
    id=0;
    sf::Clock clock;
    this->position = position;
    //diagrammSizeX und diagrammSizeY define the size of the diagramm
    this->diagrammSizeX = diagrammSizeX - 2*OFFSET;
    this->diagrammSizeY = diagrammSizeY - 2*OFFSET;
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

void ClDiagramm::draw(sf::RenderWindow & window)
{
    //in: Vector with events (BOMB,FIRE, CASUALTIES)
    //out: Graph which shows the events on a timescale and in y-direction the number of casualties

    //1. take last struct of eventsVector and calculate x-scale with time of the struct
    //2. loop through the eventsVector and count the number of CASUALTIES in each of 8 parts of the graph

    std::vector<event> fire;
    std::vector<event> bomb;

    //sets each numberCasualties = 0
    int numberCasualties[NUMBERBLOCKS];
    for (int i=0; i<NUMBERBLOCKS; i++)
    {
        numberCasualties[i]=0.0;
    }

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
            /*if((tempTime < (timeLastEvent/diagrammSizeX)*(1)*(diagrammSizeX/(float)NUMBERBLOCKS) ))
               numberCasualties[0]++;
            if (tempTime >= (timeLastEvent/diagrammSizeX)*(1)*(diagrammSizeX/(float)NUMBERBLOCKS) && (tempTime < (timeLastEvent/diagrammSizeX)*(2)*(diagrammSizeX/(float)NUMBERBLOCKS) ))
                 numberCasualties[1]++;
            if (tempTime >= (timeLastEvent/diagrammSizeX)*(2)*(diagrammSizeX/(float)NUMBERBLOCKS) && (tempTime < (timeLastEvent/diagrammSizeX)*(3)*(diagrammSizeX/(float)NUMBERBLOCKS) ))
                 numberCasualties[2]++;
            if (tempTime >= (timeLastEvent/diagrammSizeX)*(3)*(diagrammSizeX/(float)NUMBERBLOCKS) && (tempTime < (timeLastEvent/diagrammSizeX)*(4)*(diagrammSizeX/(float)NUMBERBLOCKS) ))
                 numberCasualties[3]++;
            if (tempTime >= (timeLastEvent/diagrammSizeX)*(4)*(diagrammSizeX/(float)NUMBERBLOCKS) && (tempTime < (timeLastEvent/diagrammSizeX)*(5)*(diagrammSizeX/(float)NUMBERBLOCKS) ))
                 numberCasualties[4]++;
            if (tempTime >= (timeLastEvent/diagrammSizeX)*(5)*(diagrammSizeX/(float)NUMBERBLOCKS) && (tempTime < (timeLastEvent/diagrammSizeX)*(6)*(diagrammSizeX/(float)NUMBERBLOCKS) ))
                 numberCasualties[5]++;
            if (tempTime >= (timeLastEvent/diagrammSizeX)*(6)*(diagrammSizeX/(float)NUMBERBLOCKS) && (tempTime < (timeLastEvent/diagrammSizeX)*(7)*(diagrammSizeX/(float)NUMBERBLOCKS) ))
                 numberCasualties[6]++;
            if((tempTime >= (timeLastEvent/diagrammSizeX)*(7)*(diagrammSizeX/(float)NUMBERBLOCKS) ))
               numberCasualties[7]++;*/
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

    drawBackground(window);

    drawXAxis(window);

    drawYAxis(window);


            //draw rectangles for each block

            float maxNumberCasualties=0.0;
            for (int i=0; i<NUMBERBLOCKS; i++)
            {
                if(maxNumberCasualties < numberCasualties[i])
                {
                    maxNumberCasualties = numberCasualties[i];
                }
            }

            //now the maxNumberCasualties contains the number of the most casualties per block
            sf::RectangleShape block[NUMBERBLOCKS];

            sf::Vector2f zeroPosition (position.x + OFFSET, position.y + diagrammSizeY + OFFSET);
            sf::Vector2f tempSize;
            tempSize.x = ((float)diagrammSizeX)/NUMBERBLOCKS;

            for(int i=0; i<NUMBERBLOCKS; i++)
            {
                block[i].setPosition( zeroPosition.x + (tempSize.x*i), zeroPosition.y-diagrammSizeY*(numberCasualties[i]/maxNumberCasualties) );
                tempSize.y = diagrammSizeY*(numberCasualties[i]/maxNumberCasualties);
                block[i].setSize(tempSize);
                block[i].setFillColor(sf::Color::Blue);
            }

            for(int i=0; i<NUMBERBLOCKS; i++)
            {
                window.draw(block[i]);
            }


            //draw fire
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


            //draw bomb
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

            //draw axis legned

            sf::Text textAxisX;

            textAxisX.setFont(font);
            textAxisX.setColor(sf::Color::Black);
            textAxisX.setStyle(sf::Text::Regular);
            textAxisX.setCharacterSize(10);
            textAxisX.setPosition(position.x + diagrammSizeX + 1.5*OFFSET+5, position.y + diagrammSizeY +OFFSET+1);
            textAxisX.setString(sf::String("Time"));

            window.draw(textAxisX);


            sf::Text textAxisY;

            textAxisY.setFont(font);
            textAxisY.setColor(sf::Color::Black);
            textAxisY.setStyle(sf::Text::Regular);
            textAxisY.setCharacterSize(10);
            textAxisY.setPosition(position.x + 0.5*OFFSET, position.y + 0.3*OFFSET);
            textAxisY.setString(sf::String("Casulties"));

            window.draw(textAxisY);

            //draw legend
            sf::Text textLegend;

            textLegend.setFont(font);
            textLegend.setColor(sf::Color::Black);
            textLegend.setStyle(sf::Text::Regular);
            textLegend.setCharacterSize(30);
            textLegend.setPosition(position.x + 1*OFFSET, position.y + diagrammSizeY+OFFSET +5);
            textLegend.setString(sf::String("Legende:"));

            window.draw(textLegend);

            sf::Text textLegend1;

            textLegend1.setFont(font);
            textLegend1.setColor(sf::Color::Red);
            textLegend1.setStyle(sf::Text::Regular);
            textLegend1.setCharacterSize(30);
            textLegend1.setPosition(position.x + 4*OFFSET, position.y + diagrammSizeY+OFFSET +5);
            textLegend1.setString(sf::String("Fire |"));

            window.draw(textLegend1);

            sf::Text textLegend2;

            textLegend2.setFont(font);
            textLegend2.setColor(sf::Color::Yellow);
            textLegend2.setStyle(sf::Text::Regular);
            textLegend2.setCharacterSize(30);
            textLegend2.setPosition(position.x + 6*OFFSET, position.y + diagrammSizeY+OFFSET +5);
            textLegend2.setString(sf::String("Bomb |"));

            window.draw(textLegend2);

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


                //text of the sf::text has to be converted from float to string
                textCasualties[i].setString(number);
                window.draw(textCasualties[i]);
            }

            //draw time (2) optional
            /*sf::Text textTime;

            textTime.setFont(font);
            textTime.setColor(sf::Color::Black);
            textTime.setStyle(sf::Text::Regular);
            textTime.setCharacterSize(10);
            textTime.setPosition(position.x + diagrammSizeX + 1.5*OFFSET+5, position.y + diagrammSizeY +OFFSET+1);
            textTime.setString(sf::String("Time"));

            window.draw(textTime);*/


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
