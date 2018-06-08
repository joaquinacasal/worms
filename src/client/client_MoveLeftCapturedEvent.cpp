#include "client_MoveLeftCapturedEvent.h"

MoveLeftCapturedEvent::MoveLeftCapturedEvent(SocketProtocol& _socket_protocol):
                                          socket_protocol(_socket_protocol){}

void MoveLeftCapturedEvent::send(){
  socket_protocol.send_left_arrow();
}

MoveLeftCapturedEvent::~MoveLeftCapturedEvent(){}
