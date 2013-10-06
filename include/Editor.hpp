#ifndef EDITOR_HPP_INCLUDED
#define EDITOR_HPP_INCLUDED

#include "UiLoader.hpp"
#include "SimulationArea.hpp"

class Editor : public UiLoader
{
private:
    void on_Button_Bar_clicked();
    void on_Button_WC_clicked();
    void on_Button_Wall_clicked();
    void on_Button_Fence_clicked();

    SimulationArea *SFMLArea;
public:
    Editor(string UiPath, Glib::RefPtr<Gtk::Application> app);


};


#endif // EDITOR_HPP_INCLUDED
