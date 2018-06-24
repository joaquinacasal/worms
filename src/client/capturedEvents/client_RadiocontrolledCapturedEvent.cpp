#include "client_RadiocontrolledCapturedEvent.h"

RadiocontrolledCapturedEvent::RadiocontrolledCapturedEvent(\
                              SocketProtocol& _socket_protocol, int x, int y):
                              socket_protocol(_socket_protocol){
    this->x = x;
    this->y = y;
}

void RadiocontrolledCapturedEvent::send(){
  socket_protocol.send_radiocontrolled(x, y);
}

RadiocontrolledCapturedEvent::~RadiocontrolledCapturedEvent(){}
