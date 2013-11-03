#ifndef EDITOR_HPP_INCLUDED
#define EDITOR_HPP_INCLUDED

#include "UiLoader.hpp"
#include "SimulationArea.hpp"
#include <vector>
#include "../Common/FileHandler.hpp"
#include <cctype>

enum BackgroundColor{GREY, BROWN, GREEN};

class Editor : public UiLoader
{
private:
    void on_Button_Bar_clicked();
    void on_Button_WC_clicked();
    void on_Button_Stage_clicked();
    void on_Button_Wall_clicked();
    void on_Button_Fence_clicked();
    void on_Button_Clear_clicked();
    void on_Button_Exit_clicked();

    void change_comboBox();

    void loadFile();
    void SaveFile();
    void StartSim();
    void SaveTo();

    void want_mouse();
    void remove_obj();

    void setColor(sf::Color pColor);

    SimulationArea *SFMLArea;
    ClArea *pArea;
    string SimFile;
    bool isOpen;
    bool removeObj;
    ClFileHandler *level;
    int selectedID;

public:
    Editor(string UiPath, Glib::RefPtr<Gtk::Application> app);

};


#endif // EDITOR_HPP_INCLUDED
