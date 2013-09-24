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
   Gtk::Button* pButSave;
   Gtk::Button* pButLoad;
   Gtk::Button* pButStart;
   Gtk::Window* pWinEditor;
   string UiPath;


public:
    UiLoader(string UiPath, Glib::RefPtr<Gtk::Application> app);
    bool reloadUi(string UiPath);


};
#endif // UILOADER_HPP_INCLUDED
