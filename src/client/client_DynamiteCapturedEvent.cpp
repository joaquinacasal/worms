#include "client_DynamiteCapturedEvent.h"

DynamiteCapturedEvent::DynamiteCapturedEvent(SocketProtocol& _socket_protocol):
                                          socket_protocol(_socket_protocol){}

void DynamiteCapturedEvent::send(){
  socket_protocol.send_dynamite();
}

DynamiteCapturedEvent::~DynamiteCapturedEvent(){}
