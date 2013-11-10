#include "../../include/Editor/Editor.hpp"

Editor::Editor(string UiPath, Glib::RefPtr<Gtk::Application> app) :
    UiLoader(UiPath)
{
    // Do we have a file open?
    this->isOpen = false;
    // Filename
    this->SimFile = " ";

    // initialize FileHandle
    level = new ClFileHandler();

    // maximize Window
    pWindow->set_resizable(false);

    // initialize Painting Area
    SFMLArea = new SimulationArea(*pSFMLView, *pBox, pSizeX, pSizeY, pRot, pAreaX, pAreaY, pObjLabel, pSFMLWindow);


    /// fill ComboBox with entries
    stringstream convert;
    convert<<GREY<<GREEN<<BROWN;
    string tmp(convert.str());
    pAreaColor->append(tmp.substr(0,0), "Grau");
    pAreaColor->append(tmp.substr(1,1), "Grün");
    pAreaColor->append(tmp.substr(2,2), "Braun");
    pAreaColor->set_active(1);

    // change background color
    change_comboBox();

    /// Connect Signals to Object Buttons
    pBar->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Bar_clicked));
    pWC->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_WC_clicked));
    pStage->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Stage_clicked));
    pWall->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Wall_clicked));
    pFence->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Fence_clicked));
    pExit->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Exit_clicked));

    // ..to special buttons
    pmouse->signal_clicked().connect(sigc::mem_fun(*this, &Editor::want_mouse));
    premove->signal_clicked().connect(sigc::mem_fun(*this, &Editor::remove_obj));
    pClear->signal_clicked().connect(sigc::mem_fun(*this, &Editor::on_Button_Clear_clicked));

    // To Area Color ComboBox
    pAreaColor->signal_changed().connect(sigc::mem_fun(*this, &Editor::change_comboBox));

    // ..to file related buttons
    pLoadFile->signal_clicked().connect(sigc::mem_fun(*this, &Editor::loadFile));
    pSaveFile->signal_clicked().connect(sigc::mem_fun(*this, &Editor::SaveFile));
    pStartSim->signal_clicked().connect(sigc::mem_fun(*this, &Editor::StartSim));
    pSaveTo->signal_clicked().connect(sigc::mem_fun(*this, &Editor::SaveTo));

    Gtk::Scrollbar* pscroll = pSFMLWindow->get_vscrollbar();

    pscroll->signal_value_changed().connect(sigc::mem_fun(*SFMLArea, &SimulationArea::by_scrolling));
    pscroll =  pSFMLWindow->get_hscrollbar();
    pscroll->signal_value_changed().connect(sigc::mem_fun(*SFMLArea, &SimulationArea::by_scrolling));

    // set adjustment for the size SpinButtons
    pSizeX->set_adjustment(Gtk::Adjustment::create(10.0, 10.0, 5000.0, 0.1, 0.1));
    pSizeY->set_adjustment(Gtk::Adjustment::create(10.0, 10.0, 5000.0, 0.1, 0.1));
    // ..for rotation SpinButtons
    pRot->set_adjustment(Gtk::Adjustment::create(0.0, 0.0, 360.0, 90.0, 90.0));

    // .. for Area Size
    pAreaX->set_adjustment(Gtk::Adjustment::create(2000.0, 2000.0, 10000.0, 1.0, 1.0));
    pAreaY->set_adjustment(Gtk::Adjustment::create(1000.0, 2000.0, 10000.0, 1.0, 1.0));

    pArea = SFMLArea->getArea();

    // Start Event handle
    app->run(*pWindow);


}

/// Ungrub mouse from object
void Editor::want_mouse()
{
    if(pmouse->get_active()){
        SFMLArea->box_clicked();
        pObjLabel->set_label("");
    }
}

/// remove Object
void Editor::remove_obj()
{
    if(premove->get_active()){
        SFMLArea->remove_obj();
    }
}

/// set Color of the Area
void Editor::setColor(sf::Color pColor)
{
    pArea->setBgColor(pColor);
    SFMLArea->setBgColor(pColor);
}

/// Set an Object on the Area
void Editor::set_object(string label, enum staticObjects type){
    pObjLabel->set_label(label);
    pSizeX->set_value(10.0);
    pSizeY->set_value(10.0);
    pRot->set_value(0.0);
    SFMLArea->setObject(type, sf::Vector2<float>(0.0,0.0), sf::Vector2<float>(10.0,10.0), 0.0);
}

/// Button clocked methods
void Editor::on_Button_Bar_clicked()
{
    if(pBar->get_active())
        this->set_object("Bar", BAR);
}

void Editor::on_Button_Stage_clicked()
{
    if(pStage->get_active())
        this->set_object("Bühne", STAGE);
}

void Editor::on_Button_WC_clicked()
{
    if(pWC->get_active())
        this->set_object("WC", WC);
}

void Editor::on_Button_Fence_clicked()
{
    if(pFence->get_active())
        this->set_object("Zaun", FENCE);
}

void Editor::on_Button_Wall_clicked()
{
    if(pWall->get_active())
        this->set_object("Mauer", WALL);
}

void Editor::on_Button_Exit_clicked()
{
    if(pExit->get_active())
        this->set_object("Ausgang", GATE);
}

void Editor::on_Button_Clear_clicked()
{
    SFMLArea->clearArea();
    pArea = SFMLArea->getArea();
}

/// change Color of the Area
void Editor::change_comboBox()
{
    string id = pAreaColor->get_active_id();
    int i = atoi(id.c_str());
    pArea = SFMLArea->getArea();
    switch (i)
    {
        case GREY:
            this->setColor(sf::Color(193,205,205));
            break;
        case GREEN:
            this->setColor(sf::Color(162,205,90));
            break;
        case BROWN:
            this->setColor(sf::Color(205,132, 63));
            break;
        default:
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
            enum staticObjects object = pArea->getType(i);
            string label(SFMLArea->selectLabel(object));
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
        cerr<<start;
        cerr<<system(start.c_str());
    }

}

