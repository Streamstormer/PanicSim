/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Benedikt Klotz
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    A Object that represents the ClEditor
---------------------------------------------------------------------------------------------------------------------------------------
*/

#ifndef EDITOR_HPP_INCLUDED
#define EDITOR_HPP_INCLUDED

#include "UiLoader.hpp"
#include "SimulationArea.hpp"
#include <vector>
#include "../Common/FileHandler.hpp"
#include <cctype>

enum BackgroundColor{GREY, BROWN, GREEN};

class ClEditor : public ClUiLoader
{
private:
    void set_object(enum staticObjects type);

    // Clear Area
    void on_Button_Clear_clicked();
    // Change Background Color
    void change_comboBox();

    // File related Methods
    void loadFile();
    void SaveFile();
    void SaveTo();
    // Start Simulation
    void StartSim();


    // Grab mouse
    void want_mouse();
    void remove_obj();

    void setColor(sf::Color pColor);

    ClSimulationArea *SFMLArea;
    ClArea *pArea;
    string SimFile;
    bool isOpen;
    bool removeObj;
    ClFileHandler *level;
    int selectedID;

    // Constants for Size Adjustments
    static constexpr float STEP = 1;
    static constexpr float SIZE = 1000;
    static constexpr float MIN_SIZE = 10;
    static constexpr float ROTATION = 90;

public:
    ClEditor(string UiPath, Glib::RefPtr<Gtk::Application> app);

};


#endif // EDITOR_HPP_INCLUDED
