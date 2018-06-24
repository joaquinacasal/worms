#include "server_RadiocontrolledEvent.h"

RadiocontrolledEvent::RadiocontrolledEvent(Player* player, double x, double y){
  this->player = player;
  this->x = x;
}

void RadiocontrolledEvent::run(){
  this->player->use_radiocontrolled(x);
}
