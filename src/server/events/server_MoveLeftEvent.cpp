#include "server_MoveLeftEvent.h"

MoveLeftEvent::MoveLeftEvent(Worm* worm){
  this->worm = worm;
}

void MoveLeftEvent::run(){
  this->worm->move_left();
}
