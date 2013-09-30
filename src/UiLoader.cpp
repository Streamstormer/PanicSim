#include "../include/UiLoader.hpp"

UiLoader::UiLoader(string UiPath) {
    this->UiPath = UiPath;
    this->isOpen = false;

    if ((this->builder = Gtk::Builder::create_from_file(UiPath)) == 0) {
        cerr<<"Could not open UI File:"<<UiPath;
        exit(EXIT_FAILURE);
    }

    builder->get_widget("EditorWin", pWindow);
    builder->get_widget("masterBox", pBox);
    builder->get_widget("LoadFile", pLoadFile);
    builder->get_widget("SaveFile", pSaveFile);
    builder->get_widget("StartSim", pStartSim);

    pLoadFile->signal_clicked().connect(sigc::mem_fun(*this, &UiLoader::loadFile));
    pSaveFile->signal_clicked().connect(sigc::mem_fun(*this, &UiLoader::SaveFile));
    pStartSim->signal_clicked().connect(sigc::mem_fun(*this, &UiLoader::StartSim));

}

void UiLoader::loadFile() {
    Gtk::FileChooserDialog dialog("Please choose a Simulation file to open",
                                  Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);

    //Add response buttons the the dialog:
    dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialog.add_button("Select", Gtk::RESPONSE_OK);

    int result = dialog.run();

    //Handle the response:
    switch(result) {
    case(Gtk::RESPONSE_OK): {
        cout << "Select clicked." << endl;
        cout << "File selected: " << dialog.get_filename()<< endl;
        this->isOpen = true;
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

void UiLoader::SaveFile() {

    if(this->isOpen) {
        // do something
    } else {

        Gtk::FileChooserDialog dialog("Please choose a folder to save the file",
                                      Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
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

void UiLoader::StartSim() {

}

