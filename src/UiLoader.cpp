#include "../include/UiLoader.hpp"

UiLoader::UiLoader(string UiPath, Glib::RefPtr<Gtk::Application> app)
{
    this->UiPath = UiPath;
    if (!this->reloadUi(UiPath)) {
        cerr<<"Could not open UI File:"<<UiPath;
        exit(1);
    }
    builder->get_widget("EditorWin", pWinEditor);
    builder->get_widget("SaveFile", pButSave);
    builder->get_widget("LoadFile", pButLoad);
    builder->get_widget("StartSim", pButStart);

    app->run(*pWinEditor)
;}

bool UiLoader::reloadUi(string UiPath)
{
    if ((this->builder = Gtk::Builder::create_from_file(UiPath)) == 0)
        return false;
    else
        return true;
}
