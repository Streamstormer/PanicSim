#include "../../include/Editor/UiLoader.hpp"

UiLoader::UiLoader(string UiPath)
{
    this->UiPath = UiPath;

    try {
        // construct the GUI from a xml File
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
    builder->get_widget("SFMLView", pSFMLView);
    builder->get_widget("SFMLWindow", pSFMLWindow);

    // Main Buttons
    builder->get_widget("LoadFile", pLoadFile);
    builder->get_widget("SaveFile", pSaveFile);
    builder->get_widget("SaveTo", pSaveTo);
    builder->get_widget("Clear", pClear);
    builder->get_widget("StartSim", pStartSim);

    // special buttons
    builder->get_widget("mouse", pmouse);
    pmouse->set_group(radioGroup);
    builder->get_widget("remove", premove);
    premove->set_group(radioGroup);

    // New static Objects
    builder->get_widget("bar", pBar);
    pBar->set_group(radioGroup);
    builder->get_widget("WC", pWC);
    pWC->set_group(radioGroup);
    builder->get_widget("Stage", pStage);
    pStage->set_group(radioGroup);
    builder->get_widget("Fence", pFence);
    pFence->set_group(radioGroup);
    builder->get_widget("Wall", pWall);
    pWall->set_group(radioGroup);
    builder->get_widget("Exit", pExit);
    pExit->set_group(radioGroup);

    // Label for selected Objects
    builder->get_widget("ObjectLabel", pObjLabel);
    // object Attributes
    builder->get_widget("size_x", pSizeX);
    builder->get_widget("size_y", pSizeY);
    builder->get_widget("rotation", pRot);

    // Frames with existing Objects
    builder->get_widget("ObjectFrame", pObjFrame);
    // Texture of the Area
    builder->get_widget("AreaColor", pAreaColor);

    builder->get_widget("AreaSize_x", pAreaX);
    builder->get_widget("AreaSize_y", pAreaY);

    builder->get_widget("ObjectBox", pBox);
}


