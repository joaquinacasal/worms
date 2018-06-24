#include "client_JumpBackwardCapturedEvent.h"

JumpBackwardCapturedEvent::JumpBackwardCapturedEvent(\
                                          SocketProtocol& _socket_protocol):
                                          socket_protocol(_socket_protocol){}

void JumpBackwardCapturedEvent::send(){
  socket_protocol.send_backspace();
}

JumpBackwardCapturedEvent::~JumpBackwardCapturedEvent(){}
