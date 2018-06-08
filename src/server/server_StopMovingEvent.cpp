#include "server_StopMovingEvent.h"

StopMovingEvent::StopMovingEvent(Worm* worm){
  this->worm = worm;
}

void StopMovingEvent::run(){
  this->worm->stop_moving();
}
