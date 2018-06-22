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
            double x = this->protocol.receive_double_value();
            double y = this->protocol.receive_double_value();
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

void ClientHandler::send_worm_info(size_t id, size_t life_points, double x, double y,\
                            int angle, bool is_facing_right, int team, int movement_state){
  if (!is_alive()) return;
  this->protocol.send_worm_info(id, life_points, x, y, angle, is_facing_right, team, movement_state);
}

void ClientHandler::send_worm_death_notif(size_t id, int team){
  if (!is_alive()) return;
  this->protocol.send_worm_death_notif(id, team);
}


void ClientHandler::send_stage_info(size_t width, size_t height, std::string background){
  if (!is_alive()) return;
  this->protocol.send_stage_info(width, height, background);
}

void ClientHandler::send_beam_info(double x, double y, int length, int width, int angle){
  if (!is_alive()) return;
  this->protocol.send_beam_info(x, y, length, width, angle);
}

void ClientHandler::send_dynamite_info(double x, double y, int time_to_explosion){
  if (!is_alive()) return;
  this->protocol.send_dynamite_info(x, y, time_to_explosion);
}

void ClientHandler::send_dynamite_explosion_notif(){
  if (!is_alive()) return;
  this->protocol.send_dynamite_explosion_notif();
}

void ClientHandler::send_radiocontrolled_info(size_t id, double x, double y){
  if (!is_alive()) return;
  this->protocol.send_radiocontrolled_info(id, x, y);
}

void ClientHandler::send_radiocontrolled_explosion_info(size_t id){
  if (!is_alive()) return;
  this->protocol.send_radiocontrolled_explosion_info(id);
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

void ClientHandler::send_you_win_notif(){
  if (!is_alive()) return;
  this->protocol.send_you_win_notif();
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

Player* ClientHandler::get_player(){
  return player;
}
