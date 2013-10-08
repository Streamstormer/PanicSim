#ifndef SIMULATIONAREA_HPP_INCLUDED
#define SIMULATIONAREA_HPP_INCLUDED

#include "SFML_Widget.hpp"
#include "../Simulator/Area.hpp"


using namespace std;

class SimulationArea : public SFML_Widget
{
private:
    ClArea *Area;
    Gtk::Box *ObjectBox;
    int selectedID;

    void animate();
    void draw();
    void resize();
public:
    SimulationArea(Gtk::Frame& AreaFrame, Gtk::Box& ObjectBox);
    // sf::Rect sollte später dann ein object von uns sein wie Bar oder Bühne.
    void setObject(enum staticObjects object, sf::Vector2f position, sf::Vector2f size, float rotation);
};

#endif // SIMULATIONAREA_HPP_INCLUDED
