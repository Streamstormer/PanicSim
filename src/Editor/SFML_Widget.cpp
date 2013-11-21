#include "../../include/Editor/SFML_Widget.hpp"

ClSFML_Widget::ClSFML_Widget()
{
    set_size_request();
//    set_default_size();

    set_has_window(false); // Makes this behave like an interal object rather then a parent window.
}

ClSFML_Widget::~ClSFML_Widget()
{
}

void ClSFML_Widget::on_size_allocate(Gtk::Allocation& allocation)
{
    //Do something with the space that we have actually been given:
    //(We will not be given heights or widths less than we have requested, though
    //we might get more)

    this->set_allocation(allocation);

    if(m_refGdkWindow)
    {
        m_refGdkWindow->move_resize(allocation.get_x(),
                                    allocation.get_y(),
                                    allocation.get_width(),
                                    allocation.get_height() );
        renderWindow.setSize(sf::Vector2u(allocation.get_width(),
                                          allocation.get_height()));
    }
}

void ClSFML_Widget::on_realize()
{
    Gtk::Widget::on_realize();

    if(!m_refGdkWindow)
    {
        //Create the GdkWindow:
        GdkWindowAttr attributes;
        memset(&attributes, 0, sizeof(attributes));

        Gtk::Allocation allocation = get_allocation();

        //Set initial position and size of the Gdk::Window:
        attributes.x = allocation.get_x();
        attributes.y = allocation.get_y();
        attributes.width = allocation.get_width();
        attributes.height = allocation.get_height();

        attributes.event_mask = get_events () | Gdk::EXPOSURE_MASK;
        attributes.window_type = GDK_WINDOW_CHILD;
        attributes.wclass = GDK_INPUT_OUTPUT;


        m_refGdkWindow = Gdk::Window::create(get_window(), &attributes,
                GDK_WA_X | GDK_WA_Y);
        set_has_window(true);
        set_window(m_refGdkWindow);

        // transparent background
#if GTK_VERSION_GE(3, 0)
        this->unset_background_color();
#else
        this->get_window()->set_back_pixmap(Glib::RefPtr<Gdk::Pixmap>());
#endif

        this->set_double_buffered(false);

        //make the widget receive expose events
        m_refGdkWindow->set_user_data(gobj());

        renderWindow.create(GET_WINDOW_HANDLE_FROM_GDK(m_refGdkWindow->gobj()));
    }
}

void ClSFML_Widget::on_unrealize()
{
  m_refGdkWindow.clear();

  //Call base class:
  Gtk::Widget::on_unrealize();
}

void ClSFML_Widget::display()
{
    if(m_refGdkWindow)
    {
        renderWindow.display();
    }
}

void ClSFML_Widget::invalidate()
{
    if(m_refGdkWindow)
    {
        m_refGdkWindow->invalidate(true);
    }
}
