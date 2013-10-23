#include "../../include/Editor/Editor.hpp"

Editor::Editor(string UiPath, Glib::RefPtr<Gtk::Application> app) :
    UiLoader(UiPath)
{
    this->isOpen = false;
    this->SimFile = " ";

    level = new ClFileHandler();

    pBar->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Bar_clicked));
    pWC->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_WC_clicked));
    pStage->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Stage_clicked));
    pWall->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Wall_clicked));
    pFence->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Fence_clicked));

    pClear->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Clear_clicked));

    pLoadFile->signal_clicked().connect(sigc::mem_fun(*this, &Editor::loadFile));
    pSaveFile->signal_clicked().connect(sigc::mem_fun(*this, &Editor::SaveFile));
    pStartSim->signal_clicked().connect(sigc::mem_fun(*this, &Editor::StartSim));
    pSaveTo->signal_clicked().connect(sigc::mem_fun(*this, &Editor::SaveTo));

    pSizeX->set_adjustment(Gtk::Adjustment::create(10.0, 10.0, 500.0, 0.1, 0.1));
    pSizeY->set_adjustment(Gtk::Adjustment::create(10.0, 10.0, 500.0, 0.1, 0.1));
    pRot->set_adjustment(Gtk::Adjustment::create(0.0, 0.0, 360.0, 0.1, 0.1));

    pAreaX->set_adjustment(Gtk::Adjustment::create(748.0, 748.0, 10000.0, 1.0, 1.0));
    pAreaY->set_adjustment(Gtk::Adjustment::create(710.0, 710.0, 10000.0, 1.0, 1.0));


    SFMLArea = new SimulationArea(*pSFMLWindow, *pBox, pSizeX, pSizeY, pRot, pAreaX, pAreaY);

    pArea = SFMLArea->getArea();

    /*********************
    //TO-DO: selectable Levelsize and bgColor
    //Default Values (should be removed later):
    *********************/
    pArea->setBgColor(new sf::Color(205,133,63));
    pArea->setLevelSize((new sf::Vector2i(2000,2000)));
    /****************************************/

    app->run(*pWindow);


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

void Editor::on_Button_Clear_clicked()
{
    SFMLArea->clearArea();
    pArea = SFMLArea->getArea();
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
        cout << "Select clicked." << endl;
        cout << "File selected: " << dialog.get_filename()<< endl;
        this->SimFile = dialog.get_filename();
        this->isOpen = true;
        SFMLArea->clearArea();
        ClArea *pArea = SFMLArea->getArea();
        level->readLevel(dialog.get_filename(),pArea);
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
            std::cout << "Select clicked." << std::endl;
            std::cout << "Folder selected: " << dialog.get_filename()
                      << std::endl;

            if (level->writeLevel(dialog.get_filename(), pArea) != 0)
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
        level->writeLevel(dialog.get_filename(), pArea);
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

