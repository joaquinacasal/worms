#include "client_StopMovingCapturedEvent.h"

StopMovingCapturedEvent::StopMovingCapturedEvent(SocketProtocol& _socket_protocol):
                                          socket_protocol(_socket_protocol){}

void StopMovingCapturedEvent::send(){
  socket_protocol.send_stop_moving();
}

StopMovingCapturedEvent::~StopMovingCapturedEvent(){}
