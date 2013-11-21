#include "../../include/Editor/Editor.hpp"

ClEditor::ClEditor(string UiPath, Glib::RefPtr<Gtk::Application> app) :
    ClUiLoader(UiPath)
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
    SFMLArea = new ClSimulationArea(*pSFMLView, *pBox, pSizeX, pSizeY, pRot, pAreaX, pAreaY, pObjLabel, pSFMLWindow);


    // fill ComboBox with entries
    stringstream convert;
    convert<<GREY<<GREEN<<BROWN;
    string tmp(convert.str());
    pAreaColor->append(tmp.substr(0,0), "Grau");
    pAreaColor->append(tmp.substr(1,1), "Grün");
    pAreaColor->append(tmp.substr(2,2), "Braun");
    pAreaColor->set_active(true);

    // change background color
    change_comboBox();

    // Connect Signals to Object Buttons
    pBar->signal_clicked().connect(sigc::bind<enum staticObjects>(sigc::mem_fun(*this, &ClEditor::set_object), BAR));
    pWC->signal_clicked().connect(sigc::bind<enum staticObjects>(sigc::mem_fun(*this, &ClEditor::set_object), WC));
    pStage->signal_clicked().connect(sigc::bind<enum staticObjects>(sigc::mem_fun(*this, &ClEditor::set_object), STAGE));
    pWall->signal_clicked().connect(sigc::bind<enum staticObjects>(sigc::mem_fun(*this, &ClEditor::set_object), WALL));
    pFence->signal_clicked().connect(sigc::bind<enum staticObjects>(sigc::mem_fun(*this, &ClEditor::set_object), FENCE));
    pExit->signal_clicked().connect(sigc::bind<enum staticObjects>(sigc::mem_fun(*this, &ClEditor::set_object), GATE));

    // ..to special buttons
    pmouse->signal_clicked().connect(sigc::mem_fun(*this, &ClEditor::want_mouse));
    premove->signal_clicked().connect(sigc::mem_fun(*this, &ClEditor::remove_obj));
    pClear->signal_clicked().connect(sigc::mem_fun(*this, &ClEditor::on_Button_Clear_clicked));

    // To Area Color ComboBox
    pAreaColor->signal_changed().connect(sigc::mem_fun(*this, &ClEditor::change_comboBox));

    // ..to file related buttons
    pLoadFile->signal_clicked().connect(sigc::mem_fun(*this, &ClEditor::loadFile));
    pSaveFile->signal_clicked().connect(sigc::mem_fun(*this, &ClEditor::SaveFile));
    pStartSim->signal_clicked().connect(sigc::mem_fun(*this, &ClEditor::StartSim));
    pSaveTo->signal_clicked().connect(sigc::mem_fun(*this, &ClEditor::SaveTo));

    // set adjustment for the size SpinButtons
    pSizeX->set_adjustment(Gtk::Adjustment::create(ClEditor::MIN_SIZE, ClEditor::MIN_SIZE, ClEditor::SIZE*5, ClEditor::STEP, ClEditor::STEP));
    pSizeY->set_adjustment(Gtk::Adjustment::create(ClEditor::MIN_SIZE, ClEditor::MIN_SIZE, ClEditor::SIZE*5, ClEditor::STEP, ClEditor::STEP));
    // ..for rotation SpinButtons
    pRot->set_adjustment(Gtk::Adjustment::create(0.0, 0.0, 4*ClEditor::ROTATION, ClEditor::ROTATION, ClEditor::ROTATION));

    // .. for Area Size
    pAreaX->set_adjustment(Gtk::Adjustment::create(ClEditor::SIZE*2, ClEditor::SIZE*2, ClEditor::SIZE*10, ClEditor::STEP, ClEditor::STEP));
    pAreaY->set_adjustment(Gtk::Adjustment::create(ClEditor::SIZE, ClEditor::SIZE*2, ClEditor::SIZE*10, ClEditor::STEP, ClEditor::STEP));

    pArea = SFMLArea->getArea();

    // Start Event handle
    app->run(*pWindow);


}

/// Ungrub mouse from object
void ClEditor::want_mouse()
{
    SFMLArea->box_clicked();
    pObjLabel->set_label("");
}

/// remove Object
void ClEditor::remove_obj()
{
    SFMLArea->remove_obj();
}

/// set Color of the Area
void ClEditor::setColor(sf::Color pColor)
{
    pArea->setBgColor(pColor);
    SFMLArea->setBgColor(pColor);
}

/// Set an Object on the Area
void ClEditor::set_object(enum staticObjects type){
    pObjLabel->set_label(SFMLArea->selectLabel(type));
    pSizeX->set_value(10.0);
    pSizeY->set_value(10.0);
    pRot->set_value(0.0);
    SFMLArea->setObject(type, sf::Vector2<float>(0.0,0.0), sf::Vector2<float>(10.0,10.0), 0.0);
}

void ClEditor::on_Button_Clear_clicked()
{
    SFMLArea->clearArea();
    pArea = SFMLArea->getArea();
}

/// change Color of the Area
void ClEditor::change_comboBox()
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

void ClEditor::loadFile()
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
            checkObj->signal_clicked().connect(sigc::mem_fun(*SFMLArea, &ClSimulationArea::box_clicked));
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

void ClEditor::SaveFile()
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

void ClEditor::SaveTo()
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

void ClEditor::StartSim()
{
    if(this->SimFile == " ")
        return;
    else {
        string start("PanicSim -f " + SimFile);
        system(start.c_str());
    }

}

