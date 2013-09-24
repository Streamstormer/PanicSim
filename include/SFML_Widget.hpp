#ifndef SFML_WIDGET_HPP_INCLUDED
#define SFML_WIDGET_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <gtkmm/widget.h>

class SFML_Widget : public Gtk::Widget
{
protected:
    sf::VideoMode m_vMode;

    virtual void on_size_allocate(Gtk::Allocation& allocation);
    virtual void on_realize();
    virtual void on_unrealize();

    Glib::RefPtr<Gdk::Window> m_refGdkWindow;
public:
    sf::RenderWindow renderWindow;

    SFML_Widget(sf::VideoMode mode, int size_request=-1);
    virtual ~SFML_Widget();

    void invalidate();
    void display();
};



#endif // SFML_WIDGET_HPP_INCLUDED
