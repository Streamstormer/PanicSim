#ifndef SIMULATIONAREA_HPP_INCLUDED
#define SIMULATIONAREA_HPP_INCLUDED

#include "SFML_Widget.hpp"
#include <gtkmm.h>

class SimulationArea : public SFML_Widget
{
private:
    void animate();
    void draw();
    void resize();
public:
    SimulationArea(Gtk::Box& Editor);
};

#endif // SIMULATIONAREA_HPP_INCLUDED
