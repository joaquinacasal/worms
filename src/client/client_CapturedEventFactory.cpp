#include "client_CapturedEventFactory.h"

CapturedEventFactory::CapturedEventFactory(SocketProtocol& _socket_protocol,\
                            BlockingQueue<ICapturedEvent*>& _blocking_queue) : \
                            socket_protocol(_socket_protocol),
                            blocking_queue(_blocking_queue) {}


void CapturedEventFactory::create_move_right_event(){
  blocking_queue.push(new MoveRightCapturedEvent(socket_protocol));
}

void CapturedEventFactory::create_move_left_event(){
  blocking_queue.push(new MoveLeftCapturedEvent(socket_protocol));
}

void CapturedEventFactory::create_stop_moving_event(){
  blocking_queue.push(new StopMovingCapturedEvent(socket_protocol));
}

void CapturedEventFactory::create_jump_forward_event(){
  blocking_queue.push(new JumpForwardCapturedEvent(socket_protocol));
}

void CapturedEventFactory::create_jump_backward_event(){
  blocking_queue.push(new JumpBackwardCapturedEvent(socket_protocol));
}

void CapturedEventFactory::create_dynamite_event(){
  blocking_queue.push(new DynamiteCapturedEvent(socket_protocol));
}

void CapturedEventFactory::create_radiocontrolled_event(int x, int y){
  blocking_queue.push(new RadiocontrolledCapturedEvent(socket_protocol, x, y));
}

void CapturedEventFactory::create_teletransportation_event(int x, int y){
  blocking_queue.push(new TeletransportationCapturedEvent(socket_protocol, x, y));
}

void CapturedEventFactory::create_closed_connection_event(){
  blocking_queue.push(new ClosedConnectionCapturedEvent(socket_protocol));
}

CapturedEventFactory::~CapturedEventFactory(){}
