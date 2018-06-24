#include "server_JumpForwardEvent.h"

JumpForwardEvent::JumpForwardEvent(Worm* worm){
  this->worm = worm;
}

void JumpForwardEvent::run(){
  this->worm->jump_forward();
}
