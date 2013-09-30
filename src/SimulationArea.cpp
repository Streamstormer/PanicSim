#include "../include/SimulationArea.hpp"

SimulationArea::SimulationArea(Gtk::Box& edBox): SFML_Widget(sf::VideoMode(640, 480))
{
    // add to window Box
    edBox.pack_end(*this, Gtk::PACK_EXPAND_WIDGET);
    show();

    example = 0;


    // Let the animate method be called every 50ms
    // Note: MovingCircle::animate() doesn't return any value, but signal_timeout() expects
    //       a boolean value.
    //       Using sigc::bind_return(true, ...) we get a signal returning always true.
    Glib::signal_timeout().connect(sigc::bind_return(sigc::mem_fun(this, &SimulationArea::animate),
                                       true),
                                   50);

    // Makes our draw Method beeing drawn everytime the widget itself gets drawn.
    // Note: MovingCircle::draw() doesn't accept any parameter, but signal_draw() gives one.
    //       Using sigc::hide(...) we get a signal expecting one.
    signal_draw().connect(sigc::bind_return(
                                     sigc::hide(
                                         sigc::mem_fun(this, &SimulationArea::draw)),
                                     true));

    // Everytime the widget gets resized, we need to adjust the view.
    signal_size_allocate().connect(sigc::hide(
            sigc::mem_fun(this, &SimulationArea::resize)));
}

void SimulationArea::animate()
{
    if(example)
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i pos = sf::Mouse::getPosition(renderWindow);
            if(pos.x > 0 && pos.y > 0)
                example->setPosition(pos.x, pos.y);
            std::cout<<example->getPosition().x<<std::endl;

        }
    invalidate();
}

void SimulationArea::draw()
{
    // clear widget
    renderWindow.clear();
    if(example)
        renderWindow.draw(*example);
    display();
}

void SimulationArea::resize()
{
    // Let the View fit the pixels of the window.
    sf::Vector2f lower_right(renderWindow.getSize().x,
                             renderWindow.getSize().y);

    sf::View view(lower_right * 0.5f,
                  lower_right);
    renderWindow.setView(view);
}

void SimulationArea::setObject(enum staticObjects object, int x, int y)
{
    example = new sf::CircleShape(x);

    // set the shape color to green
    example->setFillColor(sf::Color(100, 250, 50));
}
