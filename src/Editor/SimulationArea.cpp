#include "../../include/Editor/SimulationArea.hpp"

SimulationArea::SimulationArea(Gtk::Frame& AreaFrame, Gtk::Box& ObjectBox)
                               : SFML_Widget(sf::VideoMode(640, 480))
{
    // add this widget to Area Frame..
    Gtk::Container *inFrame = (Gtk::Container*) AreaFrame.get_child();
    inFrame->add(*this);
    // .. and show it
    show();

    Area = new ClArea();
    this->ObjectBox = &ObjectBox;
    selectedID = 0;

    // Let the animate method be called every 25ms
    // Note: MovingCircle::animate() doesn't return any value, but signal_timeout() expects
    //       a boolean value.
    //       Using sigc::bind_return(true, ...) we get a signal returning always true.
    Glib::signal_timeout().connect(sigc::bind_return(sigc::mem_fun(this, &SimulationArea::animate),
                                       true),
                                   25);


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
    if(selectedID){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i pos = sf::Mouse::getPosition(renderWindow);
            if(pos.x > 0 && pos.y > 0)
                Area->setPosition(selectedID, sf::Vector2<float>(pos.x, pos.y));
            sf::Vector2f temp = Area->getPosition(selectedID);
            std::cout<<temp.x<<std::endl;
        }
    }
    // make sfmlWidget invalide so that it will be redrawn
    invalidate();
}



void SimulationArea::draw()
{
    // clear widget
    renderWindow.clear();
    Area->draw(renderWindow);
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

void SimulationArea::setObject(enum staticObjects object, sf::Vector2f position, sf::Vector2f size, float rotation)
{
    static int items = 0;

    selectedID = Area->insertStObj(object, size, position, rotation);
    string label;
    switch(object){
    case BAR:
        label = "Bar";
        break;
    case STAGE:
        label = "Stage";
        break;
    case WC:
        label = "WC";
        break;
    case WALL:
        label = "Wall";
        break;
    case FENCE:
        label = "Fence";
        break;
    }

    Gtk::CheckButton *checkObj = manage(new Gtk::CheckButton(string("Object Nr.")  + (char)(selectedID+0x30) + string(": ") + label));
    ObjectBox->pack_start(*checkObj);
    checkObj->show();
}

void SimulationArea::clearArea()
{
     selectedID = 0;
     delete Area;
     Area = new ClArea();
     renderWindow.clear();
}
