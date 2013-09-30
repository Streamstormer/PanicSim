#include "../include/Editor.hpp"

Editor::Editor(string UiPath, Glib::RefPtr<Gtk::Application> app) :
    UiLoader(UiPath)
{
    SimulationArea SFML_Area(*pBox);
    app->run(*pWindow);
}
