#include <string>
#include <vector>
#include <syslog.h>
#include "server_ClientHandler.h"

using std::move;

ClientHandler::ClientHandler(Player* a_player, Socket&& socket) :
                            protocol(std::move(socket)) {
    alive = false;
    player = a_player;
  }

void ClientHandler::run() {
    alive = true;
    while (alive) {
      try {
          char code = this->protocol.receive();
          if (!alive) continue;
          IEvent* event;
          if (protocol_translator.need_coordinates(code)){
            int x = this->protocol.receive_numeric_value();
            int y = this->protocol.receive_numeric_value();
            event = protocol_translator.translate(player, code, x, y);
          } else {
            event = protocol_translator.translate(player, code);
          }
          if (event) this->safe_queue->push(event);
      } catch (std::exception& ex){
          syslog(LOG_ERR, "%s", ex.what());
      }
    }
}

void ClientHandler::send_worm_info(size_t id, size_t life_points, int x, int y,\
                            int angle, bool is_facing_right){
  if (!is_alive()) return;
  this->protocol.send_worm_info(id, life_points, x, y, angle, is_facing_right);
}

void ClientHandler::send_stage_info(size_t width, size_t height){
  if (!is_alive()) return;
  this->protocol.send_stage_info(width, height);
}

void ClientHandler::send_beam_info(int x, int y, int length, int width, int angle){
  if (!is_alive()) return;
  this->protocol.send_beam_info(x, y, length, width, angle);
}

void ClientHandler::send_dynamite_info(int x, int y, int time_to_explosion){
  if (!is_alive()) return;
  this->protocol.send_dynamite_info(x, y, time_to_explosion);
}

void ClientHandler::send_dynamite_explosion_notif(){
  if (!is_alive()) return;
  this->protocol.send_dynamite_explosion_notif();
}

void ClientHandler::send_radiocontrolled_info(int x, int y){
  if (!is_alive()) return;
  this->protocol.send_radiocontrolled_info(x, y);
}

void ClientHandler::send_turn_time_info(int turn_chrono){
  this->protocol.send_turn_time_info(turn_chrono);
}

void ClientHandler::send_start_turn_notif(){
  if (!is_alive()) return;
  this->protocol.send_start_turn_notif();
}

void ClientHandler::send_end_turn_notif(){
  if (!is_alive()) return;
  this->protocol.send_end_turn_notif();
}

void ClientHandler::send_closed_connection_notif(){
  if (!is_alive()) return;
  this->protocol.send_closed_connection_notif();
}


void ClientHandler::add_safe_queue(SafeQueue<IEvent*>* safe_queue){
  this->safe_queue = safe_queue;
}

void ClientHandler::stop(){
    alive = false;
}

bool ClientHandler::is_alive() const {
    return alive;
}

void ClientHandler::enable_queue(){
  if (!is_alive()) return;
    this->is_queue_enabled = true;
}

void ClientHandler::disable_queue(){
  if (!is_alive()) return;
    this->is_queue_enabled = false;
}
