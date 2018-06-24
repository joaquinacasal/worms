#include "client_DynamiteDrawable.h"

DynamiteDrawable::DynamiteDrawable(double x, double y, \
                                                double time_to_explosion){
    this->x = x;
    this->y = y;
    this->time_to_explosion = time_to_explosion;
}

void DynamiteDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void DynamiteDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}

double DynamiteDrawable::get_x(){
    return x;
}

double DynamiteDrawable::get_y(){
    return y;
}

double DynamiteDrawable::get_time_to_explosion(){
    return time_to_explosion;
}
