#include "client_TeletransportationCapturedEvent.h"

TeletransportationCapturedEvent::TeletransportationCapturedEvent(SocketProtocol& _socket_protocol, int x, int y):
                                          socket_protocol(_socket_protocol){
    this->x = x;
    this->y = y;
}

void TeletransportationCapturedEvent::send(){
  socket_protocol.send_teletransportation(x, y);
}

TeletransportationCapturedEvent::~TeletransportationCapturedEvent(){}
