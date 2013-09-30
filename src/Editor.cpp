#include "../include/Editor.hpp"

Editor::Editor(string UiPath, Glib::RefPtr<Gtk::Application> app) :
    UiLoader(UiPath)
{
    SFMLArea = new SimulationArea(*pBox);
    pexample->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_example_clicked));
    app->run(*pWindow);
}

void Editor::on_example_clicked()
{
    SFMLArea->setObject(rectangle, 100, 20);
}
