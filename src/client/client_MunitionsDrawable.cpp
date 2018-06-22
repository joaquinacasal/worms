#include "client_DynamiteDrawable.h"

MunitionsDrawable::MunitionsDrawable(int dynamite_m, int radiocontrolled_m, int teletransportation_m){
    this->dynamite_m = dynamite_m;
    this->radiocontrolled_m = radiocontrolled_m;
    this->teletransportation_m = teletransportation_m;
}

void MunitionsDrawable::be_drawn_by_console(ConsoleDrawer* console_drawer){
  console_drawer->draw(this);
}

void MunitionsDrawable::be_drawn(SdlWindow* window){
  window->draw(this);
}

int MunitionsDrawable::get_dynamite_munitions(){
  return dynamite_m;
}

int MunitionsDrawable::get_radiocontrolled_munitions(){
  return radiocontrolled_m;
}

int MunitionsDrawable::get_teletransportation_munitions(){
  return teletransportation_m;
}
