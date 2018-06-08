#include <iostream>
#include <iomanip>
#include "client_DrawableFactory.h"

DrawableFactory::DrawableFactory(SocketProtocol& sp, \
                                  SafeQueue<IDrawable*>& _safe_queue) : \
                                  socket_protocol(sp),
                                  safe_queue(_safe_queue) {
  connected = true;
}

void DrawableFactory::create_start_turn_drawable(){
  safe_queue.push(new StartTurnDrawable());
}

void DrawableFactory::create_end_turn_drawable(){
  safe_queue.push(new EndTurnDrawable());

}

void DrawableFactory::create_turn_time_drawable(){
  double turn_time = (double)(socket_protocol.receive_numeric_value()) / 1000;
  safe_queue.push(new TurnTimeDrawable(turn_time));
}

void DrawableFactory::create_worm_drawable(){
  size_t id = socket_protocol.receive_numeric_value();
  size_t life_points = socket_protocol.receive_numeric_value();
  double x = (double)(socket_protocol.receive_numeric_value()) / 1000;
  double y = (double)(socket_protocol.receive_numeric_value()) / 1000;
  int angle = socket_protocol.receive_numeric_value();
  bool is_facing_right = (bool)socket_protocol.receive_numeric_value();
  safe_queue.push(new WormDrawable(id, life_points, x, y, angle, is_facing_right));
}

void DrawableFactory::create_beam_drawable(){
  double x = (double)(socket_protocol.receive_numeric_value()) / 1000;
  double y = (double)(socket_protocol.receive_numeric_value()) / 1000;
  size_t length = socket_protocol.receive_numeric_value();
  size_t width = socket_protocol.receive_numeric_value();
  size_t angle = socket_protocol.receive_numeric_value();
  safe_queue.push(new BeamDrawable(x, y, length, width, angle));
}

void DrawableFactory::create_stage_drawable(){
  size_t width = socket_protocol.receive_numeric_value();
  size_t height = socket_protocol.receive_numeric_value();
  safe_queue.push(new StageDrawable(width, height));
}

void DrawableFactory::create_dynamite_drawable(){
  double x = (double)(socket_protocol.receive_numeric_value()) / 1000;
  double y = (double)(socket_protocol.receive_numeric_value()) / 1000;
  double time_to_explosion = (double)(socket_protocol.receive_numeric_value()) / 1000;
  safe_queue.push(new DynamiteDrawable(x, y, time_to_explosion));
}

void DrawableFactory::create_radiocontrolled_drawable(){
  double x = (double)(socket_protocol.receive_numeric_value()) / 1000;
  double y = (double)(socket_protocol.receive_numeric_value()) / 1000;
  safe_queue.push(new RadiocontrolledDrawable(x, y));
}

void DrawableFactory::create_closed_connection_drawable(){
  safe_queue.push(new ClosedConnectionDrawable());
}

void DrawableFactory::create_drawable(){
  char code = socket_protocol.receive();
  switch (code) {
    case PROTOCOL_TURN_START:
      create_start_turn_drawable();
      break;
    case PROTOCOL_TURN_END:
      create_end_turn_drawable();
      break;
    case PROTOCOL_TURN_TIME:
      create_turn_time_drawable();
      break;
    case PROTOCOL_WORM_INFO:
      create_worm_drawable();
      break;
    case PROTOCOL_STAGE_INFO:
      create_stage_drawable();
      break;
    case PROTOCOL_BEAM_INFO:
      create_beam_drawable();
      break;
    case PROTOCOL_DYMAMITE_INFO:
      create_dynamite_drawable();
      break;
    case PROTOCOL_RADIOCONTROLLED_INFO:
      create_radiocontrolled_drawable();
      break;
    case PROTOCOL_CLOSED_CON:
      printf("\n\n\n\n\n\n\n\nDEBUG: RECIBE EL PROTOCOL CLOSED CON\n\n\n\n\n\n\n\n\n\n\n");
      this->stop();
      create_closed_connection_drawable();
      break;
  }
}

void DrawableFactory::run(){
  while(connected) {
    create_drawable();
  }
}

bool DrawableFactory::is_connected(){
  return connected;
}


void DrawableFactory::stop(){
  connected = false;
  socket_protocol.shutdown(SHUT_RDWR);
}
