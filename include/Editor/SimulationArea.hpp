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
    Gtk::SpinButton *SizeX;
    Gtk::SpinButton *SizeY;
    Gtk::SpinButton *Rot;
    vector<Gtk::CheckButton*> CheckButt;

    void animate();
    void draw();
    void resize();
public:
    SimulationArea(Gtk::Frame& AreaFrame, Gtk::Box& ObjectBox, Gtk::SpinButton *SizeX,
                   Gtk::SpinButton *SizeY, Gtk::SpinButton *Rot);
    void clearArea();
    void setObject(enum staticObjects object, sf::Vector2f position, sf::Vector2f size, float rotation);
};

#endif // SIMULATIONAREA_HPP_INCLUDED
