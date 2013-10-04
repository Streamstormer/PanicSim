#include "../include/Editor.hpp"

Editor::Editor(string UiPath, Glib::RefPtr<Gtk::Application> app) :
    UiLoader(UiPath)
{
    SFMLArea = new SimulationArea(*pSFMLFrame);
    pBar->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Bar_clicked));
    app->run(*pWindow);
}

void Editor::on_Button_Bar_clicked()
{
    SFMLArea->setObject(rectangle, 10, 20);
}
