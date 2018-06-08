#include "server_TeletransportationEvent.h"

TeletransportationEvent::TeletransportationEvent(Player* player, int x, int y){
  this->player = player;
  this->x = x;
  this->y = y;
}

void TeletransportationEvent::run(){
  this->player->teletransport_actual_worm(x, y);
}
