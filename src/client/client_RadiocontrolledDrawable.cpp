#include "client_RadiocontrolledDrawable.h"

RadiocontrolledDrawable::RadiocontrolledDrawable(size_t id, double x, double y){
    this->id = id;
    this->x = x;
    this->y = y;
}

void RadiocontrolledDrawable::be_drawn_by_console(\
                                              ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void RadiocontrolledDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}

size_t RadiocontrolledDrawable::get_id(){
    return id;
}

double RadiocontrolledDrawable::get_x(){
    return x;
}

double RadiocontrolledDrawable::get_y(){
    return y;
}
