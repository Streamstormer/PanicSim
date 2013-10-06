#include "../include/Editor.hpp"

Editor::Editor(string UiPath, Glib::RefPtr<Gtk::Application> app) :
    UiLoader(UiPath)
{
    SFMLArea = new SimulationArea(*pSFMLFrame);

    pBar->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Bar_clicked));
    pWC->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_WC_clicked));
    pWall->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Wall_clicked));
    pFence->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Fence_clicked));

    pSizeX->set_adjustment(Gtk::Adjustment::create(10.0, 10.0, 20.0, 0.1, 0.1));
    pSizeY->set_adjustment(Gtk::Adjustment::create(10.0, 10.0, 20.0, 0.1, 0.1));
    pRotX->set_adjustment(Gtk::Adjustment::create(10.0, 10.0, 20.0, 0.1, 0.1));
    pRotY->set_adjustment(Gtk::Adjustment::create(10.0, 10.0, 20.0, 0.1, 0.1));

    app->run(*pWindow);
}

void Editor::on_Button_Bar_clicked()
{
    pObjLabel->set_label("Bar");
    SFMLArea->setObject(rectangle, sf::Vector2f(10,10), sf::Vector2f(100, 20));
}

void Editor::on_Button_WC_clicked()
{
    pObjLabel->set_label("WC");
    SFMLArea->setObject(rectangle, sf::Vector2f(10,10), sf::Vector2f(100, 20));
}


void Editor::on_Button_Fence_clicked()
{
    pObjLabel->set_label("Fence");
    SFMLArea->setObject(rectangle, sf::Vector2f(10,10), sf::Vector2f(100, 20));
}

void Editor::on_Button_Wall_clicked()
{
    pObjLabel->set_label("Wall");
    SFMLArea->setObject(rectangle, sf::Vector2f(10,10), sf::Vector2f(100, 20));
}
