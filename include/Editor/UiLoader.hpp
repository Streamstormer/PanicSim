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
    Gtk::Frame *pSFMLFrame;

    Gtk::Button *pLoadFile;
    Gtk::Button *pSaveFile;
    Gtk::Button *pSaveTo;
    Gtk::Button *pStartSim;
    Gtk::Button *pClear;

    Gtk::Button *pBar;
    Gtk::Button *pWC;
    Gtk::Button *pFence;
    Gtk::Button *pWall;

    Gtk::Frame *pObjFrame;
    Gtk::Label *pObjLabel;

    Gtk::SpinButton *pSizeX;
    Gtk::SpinButton *pSizeY;
    Gtk::SpinButton *pRotX;
    Gtk::SpinButton *pRotY;
    Gtk::SpinButton *pAreaX;
    Gtk::SpinButton *pAreaY;

    Gtk::ComboBoxText *pAreaTex;


    Gtk::Box *pBox;
    UiLoader(string UiPath);
    void loadFile();
    void SaveFile();
    void StartSim();

};
#endif // UILOADER_HPP_INCLUDED
