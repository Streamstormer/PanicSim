#include "../../include/Editor/Editor.hpp"

Editor::Editor(string UiPath, Glib::RefPtr<Gtk::Application> app) :
    UiLoader(UiPath)
{
    this->isOpen = false;
    this->SimFile = " ";
    this->removeObj = false;

    level = new ClFileHandler();

   // pWindow->fullscreen();

    SFMLArea = new SimulationArea(*pSFMLView, *pBox, pSizeX, pSizeY, pRot, pAreaX, pAreaY, pObjLabel);

    stringstream convert;
    convert<<GREY<<GREEN<<BROWN;
    string tmp(convert.str());
    pAreaColor->append(tmp.substr(0,0), "Grau");
    pAreaColor->append(tmp.substr(1,1), "Grün");
    pAreaColor->append(tmp.substr(2,2), "Braun");
    pAreaColor->set_active(1);

    change_comboBox();

    pBar->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Bar_clicked));
    pWC->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_WC_clicked));
    pStage->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Stage_clicked));
    pWall->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Wall_clicked));
    pFence->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Fence_clicked));
    pExit->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Exit_clicked));

    pmouse->signal_clicked().connect(sigc::mem_fun(*this, &Editor::want_mouse));
    premove->signal_clicked().connect(sigc::mem_fun(*this, &Editor::remove_obj));

    pClear->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Clear_clicked));

    pAreaColor->signal_changed().connect(sigc::mem_fun(*this, &Editor::change_comboBox));

    pLoadFile->signal_clicked().connect(sigc::mem_fun(*this, &Editor::loadFile));
    pSaveFile->signal_clicked().connect(sigc::mem_fun(*this, &Editor::SaveFile));
    pStartSim->signal_clicked().connect(sigc::mem_fun(*this, &Editor::StartSim));
    pSaveTo->signal_clicked().connect(sigc::mem_fun(*this, &Editor::SaveTo));

    pSizeX->set_adjustment(Gtk::Adjustment::create(10.0, 10.0, 500.0, 0.1, 0.1));
    pSizeY->set_adjustment(Gtk::Adjustment::create(10.0, 10.0, 500.0, 0.1, 0.1));
    pRot->set_adjustment(Gtk::Adjustment::create(0.0, 0.0, 360.0, 90.0, 90.0));

    pAreaX->set_adjustment(Gtk::Adjustment::create(2000.0, 2000.0, 2000.0, 1.0, 1.0));
    pAreaY->set_adjustment(Gtk::Adjustment::create(2000.0, 2000.0, 2000.0, 1.0, 1.0));

    pArea = SFMLArea->getArea();

    app->run(*pWindow);


}

void Editor::want_mouse()
{
     SFMLArea->box_clicked();
     pObjLabel->set_label("");
}

void Editor::remove_obj()
{
    SFMLArea->remove_obj();
}

void Editor::setColor(sf::Color pColor)
{
    pArea->setBgColor(pColor);
    SFMLArea->setBgColor(pColor);
}

void Editor::on_Button_Bar_clicked()
{
    pObjLabel->set_label("Bar");
    pSizeX->set_value(10.0);
    pSizeY->set_value(10.0);
    pRot->set_value(0.0);
    SFMLArea->setObject(BAR, sf::Vector2<float>(0.0,0.0), sf::Vector2<float>(10.0,10.0), 0.0);
}

void Editor::on_Button_Stage_clicked()
{
    pObjLabel->set_label("Stage");
    pSizeX->set_value(10.0);
    pSizeY->set_value(10.0);
    pRot->set_value(0.0);
    SFMLArea->setObject(STAGE, sf::Vector2<float>(0.,0.), sf::Vector2<float>(10.,10.), 0.0);

}

void Editor::on_Button_WC_clicked()
{
    pObjLabel->set_label("WC");
    pSizeX->set_value(10.0);
    pSizeY->set_value(10.0);
    pRot->set_value(0.0);
    SFMLArea->setObject(WC, sf::Vector2<float>(0.,0.), sf::Vector2<float>(10.,10.), 0.0);
}


void Editor::on_Button_Fence_clicked()
{
    pObjLabel->set_label("Fence");
    pSizeX->set_value(10.0);
    pSizeY->set_value(10.0);
    pRot->set_value(0.0);
    SFMLArea->setObject(FENCE, sf::Vector2<float>(0.,0.), sf::Vector2<float>(10.,10.), 0.0);
}

void Editor::on_Button_Wall_clicked()
{
    pObjLabel->set_label("Wall");
    pSizeX->set_value(10.0);
    pSizeY->set_value(10.0);
    pRot->set_value(0.0);
    SFMLArea->setObject(WALL, sf::Vector2<float>(0.,0.), sf::Vector2<float>(10.,10.), 0.0);
}

void Editor::on_Button_Exit_clicked()
{
    pObjLabel->set_label("Exit");
    pSizeX->set_value(10.0);
    pSizeY->set_value(10.0);
    pRot->set_value(0.0);
    SFMLArea->setObject(GATE, sf::Vector2<float>(0.,0.), sf::Vector2<float>(10.,10.), 0.0);
}

void Editor::on_Button_Clear_clicked()
{
    SFMLArea->clearArea();
    pArea = SFMLArea->getArea();
}

void Editor::change_comboBox()
{
    string id = pAreaColor->get_active_id();
    int i = atoi(id.c_str());
    pArea = SFMLArea->getArea();
    switch (i)
    {
        case GREY:
            //pArea->setBgColor(sf::Color(193,205,205));
            this->setColor(sf::Color(193,205,205));
            break;
        case GREEN:
            //pArea->setBgColor(sf::Color(162,205,90));
            this->setColor(sf::Color(162,205,90));
            break;
        case BROWN:
            //pArea->setBgColor(sf::Color(205,132, 63));
            this->setColor(sf::Color(205,132, 63));
            break;
        default:
            std::cerr<<i<<std::endl;
            break;
    }
}

void Editor::loadFile()
{
    Gtk::FileChooserDialog dialog("Bitte wählen sie eine Simulations Datei aus",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    //Add response buttons the the dialog:
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button("Auswählen", Gtk::RESPONSE_OK);

    int result = dialog.run();

    //Handle the response:
    switch(result) {
    case(Gtk::RESPONSE_OK): {
        this->SimFile = dialog.get_filename();
        this->isOpen = true;
        SFMLArea->clearArea();
        ClArea *pArea = SFMLArea->getArea();
        level->readLevel(dialog.get_filename(),pArea);
        setColor(pArea->getBgColor());
        pAreaX->set_value(pArea->getLevelSize().x);
        pAreaY->set_value(pArea->getLevelSize().y);

        for(int i=1; i<=pArea->getNumberOfStaticObjects();i++){
            int object = pArea->getType(i);
            string label;
            switch(object) {
            case BAR:
                label = "Bar";
                break;
            case STAGE:
                label = "Stage";
                break;
            case WC:
                label = "WC";
                break;
            case WALL:
                label = "Wall";
                break;
            case FENCE:
                label = "Fence";
                break;
            case GATE:
                label = "Exit";
                break;
            }

            stringstream convert;
            convert<<i;
            Gtk::CheckButton *checkObj = manage(new Gtk::CheckButton(string("Object Nr. ")  + convert.str() + string(": ") + label));
            pBox->pack_start(*checkObj);
            checkObj->signal_clicked().connect(sigc::mem_fun(*SFMLArea, &SimulationArea::box_clicked));
            checkObj->show();
            SFMLArea->insertCheck(checkObj);
        }
        break;
    }
    case(Gtk::RESPONSE_CANCEL): {
        cout << "Cancel clicked." <<endl;
        break;
    }
    default: {
        cout << "Unexpected button clicked." << endl;
        break;
    }
    }
}

void Editor::SaveFile()
{
    if(this->SimFile.length() < 1)
        this->SaveTo();

    if(this->isOpen) {
        pArea->setLevelSize(sf::Vector2i(pAreaX->get_value(), pAreaY->get_value()));
        level->writeLevel(this->SimFile, pArea);
    } else {

        Gtk::FileChooserDialog dialog("Bitte wählen sie einen Ort zu speichern aus",
                                      Gtk::FILE_CHOOSER_ACTION_SAVE);
        dialog.set_transient_for(*this);

        //Add response buttons to the dialog:
        dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
        dialog.add_button("Select", Gtk::RESPONSE_OK);

        int result = dialog.run();

        //Handle the response:
        switch(result) {
        case(Gtk::RESPONSE_OK):
            SimFile = dialog.get_filename();
            isOpen = true;
            pArea->setLevelSize(sf::Vector2i(pAreaX->get_value(), pAreaY->get_value()));
            if (level->writeLevel(SimFile, pArea) != 0)
                exit(EXIT_FAILURE);
            this->SimFile = dialog.get_filename();

            break;

        case(Gtk::RESPONSE_CANCEL):
            std::cout << "Cancel clicked." << std::endl;
            break;

        default:
            std::cout << "Unexpected button clicked." << std::endl;
            break;
        }
    }
}

void Editor::SaveTo()
{
    Gtk::FileChooserDialog dialog("Bitte wählen sie einen Ort zu speichern aus",
                                  Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*this);

    //Add response buttons to the dialog:
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button("Auswählen", Gtk::RESPONSE_OK);

    int result = dialog.run();

    //Handle the response:
    switch(result) {
    case(Gtk::RESPONSE_OK):
        std::cout << "Select clicked." << std::endl;
        std::cout << "Folder selected: " << dialog.get_filename()
                  << std::endl;
        SimFile = dialog.get_filename();
        isOpen = true;
        pArea->setLevelSize(sf::Vector2i(pAreaX->get_value(), pAreaY->get_value()));
        level->writeLevel(SimFile, pArea);

        break;

    case(Gtk::RESPONSE_CANCEL):
        std::cout << "Cancel clicked." << std::endl;
        break;

    default:
        std::cout << "Unexpected button clicked." << std::endl;
        break;
    }
}

void Editor::StartSim()
{
    if(this->SimFile == " ")
        return;
    else {
        string start("PanicSim -f " + SimFile);
        cout<<system(start.c_str());
    }

}

