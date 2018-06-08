#include "server_ClosedConnectionEvent.h"

ClosedConnectionEvent::ClosedConnectionEvent(){}

void ClosedConnectionEvent::run(){
  throw std::runtime_error("El cliente cerró la conexión");
}
