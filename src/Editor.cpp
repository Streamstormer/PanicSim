#include "../include/Editor.hpp"

Editor::Editor(string UiPath, Glib::RefPtr<Gtk::Application> app) :
    UiLoader(UiPath)
{
    app->run(*pWindow);
}
