#include "server_DynamiteEvent.h"

DynamiteEvent::DynamiteEvent(Player* player){
  this->player = player;
}

void DynamiteEvent::run(){
  this->player->use_dynamite();
}
