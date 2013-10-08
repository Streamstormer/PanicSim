#include "../../include/Editor/UiLoader.hpp"

UiLoader::UiLoader(string UiPath)
{
    this->UiPath = UiPath;
    this->isOpen = false;
    this->SimFile = " ";

    try {
        this->builder = Gtk::Builder::create_from_file(UiPath);
    } catch(const Glib::FileError& ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    } catch(const Glib::MarkupError& ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    } catch(const Gtk::BuilderError& ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    // Main Window
    builder->get_widget("EditorWin", pWindow);

    // SFML Frame
    builder->get_widget("SFML_Frame", pSFMLFrame);

    // Main Buttons
    builder->get_widget("LoadFile", pLoadFile);
    builder->get_widget("SaveFile", pSaveFile);
    builder->get_widget("SaveTo", pSaveTo);
    builder->get_widget("Clear", pClear);
    builder->get_widget("StartSim", pStartSim);

    // New static Objects
    builder->get_widget("bar", pBar);
    builder->get_widget("WC", pWC);
    builder->get_widget("Fence", pFence);
    builder->get_widget("Wall", pWall);

    // Label for selected Objects
    builder->get_widget("ObjectLabel", pObjLabel);
    // object Attributes
    builder->get_widget("size_x", pSizeX);
    builder->get_widget("size_y", pSizeY);
    builder->get_widget("rotation", pRot);

    // Frames with existing Objects
    builder->get_widget("ObjectFrame", pObjFrame);
    // Texture of the Area
    builder->get_widget("AreaTextures", pAreaTex);

    builder->get_widget("AreaSize_x", pAreaX);
    builder->get_widget("AreaSize_y", pAreaY);

    pLoadFile->signal_clicked().connect(sigc::mem_fun(*this, &UiLoader::loadFile));
    pSaveFile->signal_clicked().connect(sigc::mem_fun(*this, &UiLoader::SaveFile));
    pStartSim->signal_clicked().connect(sigc::mem_fun(*this, &UiLoader::StartSim));
    pSaveTo->signal_clicked().connect(sigc::mem_fun(*this, &UiLoader::SaveTo));
    pClear->signal_clicked().connect(sigc::mem_fun(*this, &UiLoader::Clear));

}

void UiLoader::loadFile()
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

void UiLoader::SaveFile()
{

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

void UiLoader::SaveTo()
{
    Gtk::FileChooserDialog dialog("Bitte wählen sie einen Ort zu spiechern aus",
                                  Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
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
        break;

    case(Gtk::RESPONSE_CANCEL):
        std::cout << "Cancel clicked." << std::endl;
        break;

    default:
        std::cout << "Unexpected button clicked." << std::endl;
        break;
    }
}

void UiLoader::StartSim()
{
    if(this->SimFile == " ")
        return;
    else {
        string start("PanicSim -f " + SimFile);
        cout<<system(start.c_str());
    }

}

void UiLoader::Clear()
{

}
