#ifndef SIMULATIONAREA_HPP_INCLUDED
#define SIMULATIONAREA_HPP_INCLUDED

#include "SFML_Widget.hpp"
#include <gtkmm.h>
#include <iostream>

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
    SimulationArea(Gtk::Box& Editor);
    // sf::Rect sollte später dann ein object von uns sein wie Bar oder Bühne.
    void setObject(enum staticObjects, int x, int y);
};

#endif // SIMULATIONAREA_HPP_INCLUDED
