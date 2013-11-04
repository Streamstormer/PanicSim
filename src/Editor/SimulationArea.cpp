#include "../../include/Editor/SimulationArea.hpp"

SimulationArea::SimulationArea(Gtk::Viewport& AreaWin, Gtk::Box& ObjectBox, Gtk::SpinButton *SizeX,
                               Gtk::SpinButton *SizeY, Gtk::SpinButton *Rot, Gtk::SpinButton *pAreaSizeX,
                               Gtk::SpinButton *pAreaSizeY, Gtk::Label *pObjLabel)
    // hardcode size to 2000x2000 as workaround for the size issues under Windows
    : SFML_Widget(sf::VideoMode(2000, 2000))
{
    // add this widget to Area Frame..
    AreaWin.add(*this);
    // .. and show it
    show();

    Port = &AreaWin;

    Area = new ClArea();
    this->ObjectBox = &ObjectBox;
    selectedID = 0;
    this->SizeX = SizeX;
    this->SizeY = SizeY;
    this->Rot = Rot;
    this->boxChecked = false;
    this->pAreaSizeX = pAreaSizeX;
    this->pAreaSizeY = pAreaSizeY;
    this->pObjLabel = pObjLabel;

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
    int rightID = 0;
    if(boxChecked) {
        for(unsigned int i = 0; i<CheckButt.size(); i++) {
            if(CheckButt[i]->get_active()) {
                int ID;

                string label(CheckButt[i]->get_label());
                size_t startPos = label.find_first_of('.');
                size_t endPos = label.find_first_of(':');
                stringstream convert(label.substr(startPos+2,  endPos - (startPos+2)));
                cerr<<convert.str();
                convert >> ID;

                if(selectedID != ID){
                    SizeX->set_value(Area->getSize(ID).x);
                    SizeY->set_value(Area->getSize(ID).y);
                    Rot->set_value(Area->getRotation(ID));
                    string label(this->selectLabel(Area->getType(ID)));

                    pObjLabel->set_label(label);
                    rightID = ID;

                } else
                    CheckButt[i]->set_active(false);
            }
        }
        selectedID = rightID;
        boxChecked = false;
        if(!selectedID)
            pObjLabel->set_label("");
    }
    if(selectedID) {
        Area->setSize(selectedID, sf::Vector2f(SizeX->get_value(), SizeY->get_value()));
        Area->setRotation(selectedID, Rot->get_value());

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i pos = sf::Mouse::getPosition(renderWindow);
            std::cerr<<pos.x<<" "<<pos.y<<std::endl;

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
    renderWindow.clear(bgColor);
    //renderWindow.close();
    Area->draw(renderWindow);
    display();
}

void SimulationArea::resize()
{
/// This code is not working, but it could be that some part of it can be used...
#if 0
    sf::Event event;
    while(renderWindow.pollEvent(event))
        if(event.type == sf::Event::Resized){
                set_size_request(event.size.width, event.size.height);
                std::cerr<<"hello"<<std::endl;
        }*/


    // Let the View fit the pixels of the window.
    sf::Vector2f lower_right(renderWindow.getSize().x,
                             renderWindow.getSize().y);



    std::cerr<<renderWindow.getSize().x<<std::endl;
    std::cerr<<renderWindow.getSize().y<<std::endl;
    std::cerr<<Port->get_height()<<std::endl;
    std::cerr<<Port->get_width()<<std::endl;

    if(Port->get_height() >= renderWindow.getSize().x){
        sf::VideoMode mode(Port->get_height(), renderWindow.getSize().y);
        set_size_request(mode.width, mode.height);
        renderWindow.setSize(sf::Vector2u(mode.width, mode.height));
    }
    if(Port->get_width() >= renderWindow.getSize().y){
        sf::VideoMode mode(renderWindow.getSize().y, Port->get_width());
        set_size_request(mode.width, mode.height);
        renderWindow.setSize(sf::Vector2u(mode.width, mode.height));
    }
    std::cerr<<"End"<<renderWindow.getSize().x<<std::endl;
    std::cerr<<renderWindow.getSize().y<<std::endl;
                // Let the View fit the pixels of the window.
    sf::Vector2f lower_right(renderWindow.getSize().x,
                            renderWindow.getSize().y);

    //pAreaSizeX->set_value(renderWindow.getSize().x);
    //pAreaSizeY->set_value(renderWindow.getSize().y);

    sf::View view(sf::FloatRect(0, 0, renderWindow.getSize().x, renderWindow.getSize().y));
    renderWindow.setView(view);
#endif
}

void SimulationArea::setObject(enum staticObjects object, sf::Vector2f position, sf::Vector2f size, float rotation)
{
    if(selectedID!=0){
        boxChecked = true;
        animate();
    }
    selectedID = Area->insertStObj(object, size, position, rotation);
    string label(this->selectLabel(object));

    stringstream convert;
    convert<<selectedID;
    Gtk::CheckButton *checkObj = manage(new Gtk::CheckButton(string("Objekt Nr. ")  + convert.str() + string(": ") + label));
    ObjectBox->pack_start(*checkObj);
    checkObj->set_active();

    checkObj->signal_clicked().connect(sigc::mem_fun(*this, &SimulationArea::box_clicked));
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
    for(int i = 0; i<size; i++) {
        Gtk::Widget *tmp = childrens.back();
        childrens.pop_back();
        ObjectBox->remove(*tmp);
        delete tmp;
    }
    renderWindow.clear();
}

void SimulationArea::remove_obj()
{
    box_clicked();
    Area->removeObj(selectedID);
}

void SimulationArea::box_clicked()
{
    boxChecked = true;
}

ClArea *SimulationArea::getArea()
{
    return Area;
}

void SimulationArea::insertCheck(Gtk::CheckButton *check)
{
    this->CheckButt.push_back(check);
}

string SimulationArea::selectLabel(enum staticObjects type){
    switch(type) {
        case BAR:
            return "Bar";
        case STAGE:
            return "Bühne";
        case WC:
            return "WC";
        case WALL:
            return "Mauer";
        case FENCE:
            return "Zaun";
        case GATE:
            return "Ausgang";
    }
    return "";
}
