/*
---------------------------------------------------------------------------------------------------------------------------------------
Support:    Benedikt Klotz
---------------------------------------------------------------------------------------------------------------------------------------
usecase:    A low level Bridge between SFML and GTKmm.
---------------------------------------------------------------------------------------------------------------------------------------
*/


#ifndef SFML_WIDGET_HPP_INCLUDED
#define SFML_WIDGET_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <gtkmm.h>
#include <iostream>

#if defined(SFML_SYSTEM_WINDOWS)

#include <gdk/gdkwin32.h>
#define GET_WINDOW_HANDLE_FROM_GDK (HWND)gdk_win32_window_get_handle

#elif defined(SFML_SYSTEM_LINUX) || defined(SFML_SYSTEM_FREEBSD)

#include <gdk/gdkx.h>
#define GET_WINDOW_HANDLE_FROM_GDK GDK_WINDOW_XID

#elif defined(SFML_SYSTEM_MACOS)

#error Note: You have to figure out an analogue way to access the handle of the widget on a Mac-System

#else

#error Unsupported Operating System

#endif

class ClSFML_Widget : public Gtk::Widget
{
protected:
    sf::VideoMode m_vMode;
    sf::RenderWindow renderWindow;

    virtual void on_size_allocate(Gtk::Allocation& allocation);
    virtual void on_realize();
    virtual void on_unrealize();

    Glib::RefPtr<Gdk::Window> m_refGdkWindow;
public:
    ClSFML_Widget();
    virtual ~ClSFML_Widget();

    void invalidate();
    void display();
};



#endif // SFML_WIDGET_HPP_INCLUDED
