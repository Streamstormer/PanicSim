#ifndef SIMULATIONAREA_HPP_INCLUDED
#define SIMULATIONAREA_HPP_INCLUDED

#include "SFML_Widget.hpp"


using namespace std;

enum staticObjects{rectangle, shape, etc };

class SimulationArea : public SFML_Widget
{
private:
    sf::CircleShape *example;
    sf::Event mouseEvent;
    void animate();
    void draw();
    void resize();
public:
    SimulationArea(Gtk::Frame& AreaFrame);
    // sf::Rect sollte später dann ein object von uns sein wie Bar oder Bühne.
    void setObject(enum staticObjects, sf::Vector2f size, sf::Vector2f rotation);
};

#endif // SIMULATIONAREA_HPP_INCLUDED
