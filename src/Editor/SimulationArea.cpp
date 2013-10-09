#include "../../include/Editor/SimulationArea.hpp"

SimulationArea::SimulationArea(Gtk::Frame& AreaFrame, Gtk::Box& ObjectBox, Gtk::SpinButton *SizeX,
                               Gtk::SpinButton *SizeY, Gtk::SpinButton *Rot)
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
    this->SizeX = SizeX;
    this->SizeY = SizeY;
    this->Rot = Rot;
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
    bool oneChecked = false;
    for(unsigned int i = 0;i<CheckButt.size();i++){
        if(CheckButt[i]->get_active() && !oneChecked){
            oneChecked = true;
            string label(CheckButt[i]->get_label());
            size_t startPos = label.find_first_of('.');
            size_t endPos = label.find_first_of(':');
            stringstream convert(label.substr(startPos+2,  endPos - (startPos+2)));
            convert >> selectedID;
            SizeX->set_value(Area->getSize(selectedID).x);
            SizeY->set_value(Area->getSize(selectedID).y);
            Rot->set_value(Area->getRotation(selectedID));
        }
        else if(CheckButt[i]->get_active() && oneChecked)
            CheckButt[i]->set_active(false);
    }
    if(selectedID){
        Area->setSize(selectedID, sf::Vector2f(SizeX->get_value(), SizeY->get_value()));
        Area->setRotation(selectedID, Rot->get_value());
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i pos = sf::Mouse::getPosition(renderWindow);
            if(pos.x > 0 && pos.y > 0)
                Area->setPosition(selectedID, sf::Vector2<float>(pos.x, pos.y));
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

    stringstream convert;
    convert<<selectedID;
    Gtk::CheckButton *checkObj = manage(new Gtk::CheckButton(string("Object Nr. ")  + convert.str() + string(": ") + label));
    ObjectBox->pack_start(*checkObj);
    checkObj->show();
    CheckButt.push_back(checkObj);
}

void SimulationArea::clearArea()
{
     selectedID = 0;
     delete Area;
     Area = new ClArea();
     CheckButt.clear();
     vector<Gtk::Widget*> childrens = ObjectBox->get_children();
     int size = childrens.size();
     for(int i = 0; i<size;i++){
        Gtk::Widget *tmp = childrens.back();
        childrens.pop_back();
        ObjectBox->remove(*tmp);
        delete tmp;
     }
     renderWindow.clear();
}
