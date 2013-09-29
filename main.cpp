#include "include/Editor.hpp"
#include <unistd.h>

int main(int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "SimEditor");
    Editor Window("SimEditor.glade", app);
}
