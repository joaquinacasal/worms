#include "server_MoveRightEvent.h"

MoveRightEvent::MoveRightEvent(Worm* worm){
  this->worm = worm;
}

void MoveRightEvent::run(){
  this->worm->move_right();
}
