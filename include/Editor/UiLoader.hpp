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
    Gtk::Viewport *pSFMLView;

    Gtk::Button *pLoadFile;
    Gtk::Button *pSaveFile;
    Gtk::Button *pSaveTo;
    Gtk::Button *pStartSim;
    Gtk::Button *pClear;

    Gtk::RadioButton *pmouse;
    Gtk::RadioButton *premove;

    Gtk::RadioButton *pBar;
    Gtk::RadioButton *pWC;
    Gtk::RadioButton *pStage;
    Gtk::RadioButton *pFence;
    Gtk::RadioButton *pWall;
    Gtk::RadioButton *pExit;
    Gtk::RadioButton::Group radioGroup;

    Gtk::Frame *pObjFrame;
    Gtk::Label *pObjLabel;

    Gtk::SpinButton *pSizeX;
    Gtk::SpinButton *pSizeY;
    Gtk::SpinButton *pRot;
    Gtk::SpinButton *pAreaX;
    Gtk::SpinButton *pAreaY;

    Gtk::ComboBoxText *pAreaColor;

    Gtk::Box *pBox;
    UiLoader(string UiPath);


};
#endif // UILOADER_HPP_INCLUDED
