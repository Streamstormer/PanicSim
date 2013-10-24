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

protected:
    Gtk::Window *pWindow;
    Gtk::ScrolledWindow *pSFMLWindow;

    Gtk::Button *pLoadFile;
    Gtk::Button *pSaveFile;
    Gtk::Button *pSaveTo;
    Gtk::Button *pStartSim;
    Gtk::Button *pClear;

    Gtk::Button *pBar;
    Gtk::Button *pWC;
    Gtk::Button *pStage;
    Gtk::Button *pFence;
    Gtk::Button *pWall;
    Gtk::Button *pExit;

    Gtk::Frame *pObjFrame;
    Gtk::Label *pObjLabel;

    Gtk::SpinButton *pSizeX;
    Gtk::SpinButton *pSizeY;
    Gtk::SpinButton *pRot;
    Gtk::SpinButton *pAreaX;
    Gtk::SpinButton *pAreaY;

    Gtk::ComboBoxText *pAreaTex;

    Gtk::Box *pBox;
    UiLoader(string UiPath);


};
#endif // UILOADER_HPP_INCLUDED
