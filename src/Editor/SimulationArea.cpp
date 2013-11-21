#include "../../include/Editor/SimulationArea.hpp"

ClSimulationArea::ClSimulationArea(Gtk::Viewport& AreaWin, Gtk::Box& ObjectBox, Gtk::SpinButton *SizeX,
                               Gtk::SpinButton *SizeY, Gtk::SpinButton *Rot, Gtk::SpinButton *pAreaSizeX,
                               Gtk::SpinButton *pAreaSizeY, Gtk::Label *pObjLabel, Gtk::ScrolledWindow* scrollWin)
    // initialize SFML_Widget
    : ClSFML_Widget()
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
    this->pView = &AreaWin;
    this->pscroll = scrollWin;


    // Let the animate method be called every 25ms
    Glib::signal_timeout().connect(sigc::bind_return(sigc::mem_fun(this, &ClSimulationArea::animate),
                                   true),
                                   25);


    // Makes the draw Method being drawn everytime the widget itself gets drawn.
    signal_draw().connect(sigc::bind_return(
                              sigc::hide(
                                  sigc::mem_fun(this, &ClSimulationArea::draw)),
                              true));


}

void ClSimulationArea::animate()
{
    // get Scrollbars and set range
    Gtk::Scrollbar* pHScrollBar = pscroll->get_hscrollbar();
    Gtk::Scrollbar* pVScrollBar = pscroll->get_vscrollbar();
    pHScrollBar->set_range(0.0, pAreaSizeX->get_value());
    pVScrollBar->set_range(0.0, pAreaSizeY->get_value());

    Glib::RefPtr<Gdk::Window> GtkWin = pView->get_view_window();
    unsigned int x,y, h, w;

    // get the parameters of the gdk window
    w = GtkWin->get_width();
    h = GtkWin->get_height();
    x = pHScrollBar->get_value();
    y = pVScrollBar->get_value();

    // Only update gdk Window if something changed
    static unsigned int sX = 0, sY = 0;
    if(sX!=x||sY!=y){
        GtkWin->scroll(x,y);
        sX = x, sY = y;
    }

    // update SFML View
    sf::View view1(sf::FloatRect(x, y, w, h));
    renderWindow.setView(view1);

    int rightID = 0;
    // If a Checkbox is checked...
    if(boxChecked) {
        // ...check all Checkboxes if there are active...
        for(unsigned int i = 0; i<CheckButt.size(); i++) {
            if(CheckButt[i]->get_active()) {
                int ID;

                string label(CheckButt[i]->get_label());
                size_t startPos = label.find_first_of('.');
                size_t endPos = label.find_first_of(':');
                stringstream convert(label.substr(startPos+2,  endPos - (startPos+2)));
                convert >> ID;
                //  ...and it is not the a old active box make it the new activ object
                if(selectedID != ID){
                    SizeX->set_value(Area->getSize(ID).x);
                    SizeY->set_value(Area->getSize(ID).y);
                    Rot->set_value(Area->getRotation(ID));
                    string label(this->selectLabel(Area->getType(ID)));

                    pObjLabel->set_label(label);
                    rightID = ID;

                // and deactivate the old checkbox
                } else
                    CheckButt[i]->set_active(false);
            }
        }
        selectedID = rightID;
        boxChecked = false;
    }
    // If a object is active
    if(selectedID) {

        // Set all Values of the active object
        Area->setSize(selectedID, sf::Vector2f(SizeX->get_value(), SizeY->get_value()));
        Area->setRotation(selectedID, Rot->get_value());

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i pos = sf::Mouse::getPosition(renderWindow);

            if(pos.x > 0 && pos.y > 0)
                Area->setPosition(selectedID, sf::Vector2<float>(pos.x+pHScrollBar->get_value(), pos.y+pVScrollBar->get_value()));
        }
    }
    // make SFML_Widget invalid so that it will be redrawn
    invalidate();
}



void ClSimulationArea::draw()
{
    // clear widget
    renderWindow.clear(bgColor);
    //renderWindow.close();
    Area->draw(renderWindow);

    display();
}

void ClSimulationArea::setObject(enum staticObjects object, sf::Vector2f position, sf::Vector2f size, float rotation)
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

    checkObj->signal_clicked().connect(sigc::mem_fun(*this, &ClSimulationArea::box_clicked));
    checkObj->show();
    CheckButt.push_back(checkObj);
}

void ClSimulationArea::clearArea()
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

void ClSimulationArea::remove_obj()
{
    box_clicked();
    Area->removeObj(selectedID);
    for(unsigned int i=0; i< CheckButt.size();i++){
        if(CheckButt[i]->get_active()){
            delete CheckButt[i];
            CheckButt.erase(CheckButt.begin()+i);
        }
    }
}

void ClSimulationArea::box_clicked()
{
    boxChecked = true;
}

ClArea *ClSimulationArea::getArea()
{
    return Area;
}

void ClSimulationArea::insertCheck(Gtk::CheckButton *check)
{
    this->CheckButt.push_back(check);
}

string ClSimulationArea::selectLabel(enum staticObjects type){
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
