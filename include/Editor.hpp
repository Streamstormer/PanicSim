#ifndef EDITOR_HPP_INCLUDED
#define EDITOR_HPP_INCLUDED

#include "UiLoader.hpp"

class Editor : public UiLoader
{
private:
public:
    Editor(string UiPath, Glib::RefPtr<Gtk::Application> app);

};


#endif // EDITOR_HPP_INCLUDED
