#include "client_TurnTimeDrawable.h"

TurnTimeDrawable::TurnTimeDrawable(double t){
  this->time_left = t;
}

void TurnTimeDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void TurnTimeDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}

double TurnTimeDrawable::get_time_left(){
  return this->time_left;
}
