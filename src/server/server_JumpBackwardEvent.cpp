#include "server_JumpBackwardEvent.h"

JumpBackwardEvent::JumpBackwardEvent(Worm* worm){
  this->worm = worm;
}

void JumpBackwardEvent::run(){
  this->worm->jump_backward();
}
