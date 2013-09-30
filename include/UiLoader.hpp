#ifndef UILOADER_HPP_INCLUDED
#define UILOADER_HPP_INCLUDED

#include <gtkmm.h>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


class UiLoader : public Gtk::Window
{
private:
   Glib::RefPtr<Gtk::Builder> builder;
   string UiPath;
   bool isOpen;


protected:
    Gtk::Window *pWindow;
    Gtk::Button *pLoadFile;
    Gtk::Button *pSaveFile;
    Gtk::Button *pStartSim;
    Gtk::Box *pBox;
    UiLoader(string UiPath);
    void loadFile();
    void SaveFile();
    void StartSim();

};
#endif // UILOADER_HPP_INCLUDED
