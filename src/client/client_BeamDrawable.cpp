#include "client_BeamDrawable.h"

BeamDrawable::BeamDrawable(double x, double y, int length, int width,\
                           int angle){
  this->x = x;
  this->y = y;
  this->length = length;
  this->width = width;
  this->angle = angle;
}

void BeamDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void BeamDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}

double BeamDrawable::get_x(){
  return x;
}

double BeamDrawable::get_y(){
  return y;
}

int BeamDrawable::get_length(){
  return length;
}

int BeamDrawable::get_width(){
  return width;
}

int BeamDrawable::get_angle(){
  return angle;
}
