#include "client_MoveRightCapturedEvent.h"

MoveRightCapturedEvent::MoveRightCapturedEvent(SocketProtocol& _socket_protocol):
                                          socket_protocol(_socket_protocol){}

void MoveRightCapturedEvent::send(){
  socket_protocol.send_right_arrow();
}

MoveRightCapturedEvent::~MoveRightCapturedEvent(){}
