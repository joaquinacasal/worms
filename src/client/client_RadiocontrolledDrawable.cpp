#include "client_RadiocontrolledDrawable.h"

RadiocontrolledDrawable::RadiocontrolledDrawable(double x, double y){
    this->x = x;
    this->y = y;
}

void RadiocontrolledDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void RadiocontrolledDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}

double RadiocontrolledDrawable::get_x(){
    return x;
}

double RadiocontrolledDrawable::get_y(){
    return y;
}
