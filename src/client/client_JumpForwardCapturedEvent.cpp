#include "client_JumpForwardCapturedEvent.h"

JumpForwardCapturedEvent::JumpForwardCapturedEvent(\
                                          SocketProtocol& _socket_protocol):\
                                          socket_protocol(_socket_protocol){}

void JumpForwardCapturedEvent::send(){
  socket_protocol.send_enter();
}

JumpForwardCapturedEvent::~JumpForwardCapturedEvent(){}
