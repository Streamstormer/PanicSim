#include "../../include/Editor/Editor.hpp"

Editor::Editor(string UiPath, Glib::RefPtr<Gtk::Application> app) :
    UiLoader(UiPath)
{
    SFMLArea = new SimulationArea(*pSFMLFrame, *pBox);

    pBar->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Bar_clicked));
    pWC->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_WC_clicked));
    pStage->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Stage_clicked));
    pWall->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Wall_clicked));
    pFence->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Fence_clicked));

    pSizeX->set_adjustment(Gtk::Adjustment::create(10.0, 10.0, 20.0, 0.1, 0.1));
    pSizeY->set_adjustment(Gtk::Adjustment::create(10.0, 10.0, 20.0, 0.1, 0.1));
    pRot->set_adjustment(Gtk::Adjustment::create(10.0, 10.0, 20.0, 0.1, 0.1));

    app->run(*pWindow);
}

void Editor::on_Button_Bar_clicked()
{
    pObjLabel->set_label("Bar");
    SFMLArea->setObject(BAR, sf::Vector2<float>(10.0,10.0), sf::Vector2<float>(100.0,100.0), 0.0);
}

void Editor::on_Button_Stage_clicked()
{
    pObjLabel->set_label("Stage");
    SFMLArea->setObject(STAGE, sf::Vector2<float>(0.,0.), sf::Vector2<float>(10.,10.), 0.0);
}

void Editor::on_Button_WC_clicked()
{
    pObjLabel->set_label("WC");
    SFMLArea->setObject(WC, sf::Vector2<float>(0.,0.), sf::Vector2<float>(10.,10.), 0.0);
}


void Editor::on_Button_Fence_clicked()
{
    pObjLabel->set_label("Fence");
    SFMLArea->setObject(FENCE, sf::Vector2<float>(0.,0.), sf::Vector2<float>(10.,10.), 0.0);
}

void Editor::on_Button_Wall_clicked()
{
    pObjLabel->set_label("Wall");
    SFMLArea->setObject(WALL, sf::Vector2<float>(0.,0.), sf::Vector2<float>(10.,10.), 0.0);
}
