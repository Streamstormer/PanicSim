#include <iostream>
#include "include/UiLoader.hpp"


int main(int argc, char *argv[])
{
    cout << "Hello world!" << endl;
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "SimEditor");
    UiLoader Apploader("SimEditor.glade", app);


}
