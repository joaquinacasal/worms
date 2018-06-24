#include "client_ClosedConnectionCapturedEvent.h"

ClosedConnectionCapturedEvent::ClosedConnectionCapturedEvent(\
                                          SocketProtocol& _socket_protocol):
                                          socket_protocol(_socket_protocol){
  _continue_sending = false;
}

void ClosedConnectionCapturedEvent::send(){
  socket_protocol.send_closed_connection_notif();
}

ClosedConnectionCapturedEvent::~ClosedConnectionCapturedEvent(){}
