#include "server_NotifierThread.h"

NotifierThread::NotifierThread(){
  continue_sending = true;
}

void NotifierThread::run(){
  INotification* notification = NULL;
  while (continue_sending || blocking_queue.size() > 0) {
    blocking_queue.pop(notification);
    if (notification) {
      notification->run();
      delete notification;
    }
  }
}

void NotifierThread::stop(){
  continue_sending = false;
  blocking_queue.push(NULL);
}


void NotifierThread::send_worm_info(ClientHandler* client, size_t id, size_t life_points, int x, int y, \
                            int angle, bool is_facing_right, int team){
  if (continue_sending)
    blocking_queue.push(new WormNotification(client, id, life_points, x, y, angle, is_facing_right, team));
}

void NotifierThread::send_worm_death_notif(ClientHandler* client, size_t id){
  if (continue_sending)
    blocking_queue.push(new WormDeathNotification(client, id));
}


void NotifierThread::send_stage_info(ClientHandler* client, size_t width, size_t height, std::string background){
  if (continue_sending)
    blocking_queue.push(new StageNotification(client, width, height, background));
}

void NotifierThread::send_beam_info(ClientHandler* client, int x, int y, int length, int width, int angle){
  if (continue_sending)
    blocking_queue.push(new BeamNotification(client, x, y, length, width, angle));
}

void NotifierThread::send_dynamite_info(ClientHandler* client, int x, int y, int time_to_explosion){
  if (continue_sending)
    blocking_queue.push(new DynamiteNotification(client, x, y, time_to_explosion));
}

void NotifierThread::send_dynamite_explosion_info(ClientHandler* client){
  if (continue_sending)
    blocking_queue.push(new DynamiteExplosionNotification(client));
}


void NotifierThread::send_radiocontrolled_info(ClientHandler* client, size_t id, int x, int y){
  if (continue_sending)
    blocking_queue.push(new RadiocontrolledNotification(client, id, x, y));
}

void NotifierThread::send_radiocontrolled_explosion_info(ClientHandler* client, size_t id){
  blocking_queue.push(new RadiocontrolledExplosionNotification(client, id));
}


void NotifierThread::send_turn_time_info(ClientHandler* client, int turn_chrono){
  if (continue_sending)
    blocking_queue.push(new TurnTimeNotification(client, turn_chrono));
}

void NotifierThread::send_start_turn_notif(ClientHandler* client){
  if (continue_sending)
    blocking_queue.push(new StartTurnNotification(client));
}

void NotifierThread::send_end_turn_notif(ClientHandler* client){
  if (continue_sending)
    blocking_queue.push(new EndTurnNotification(client));
}

void NotifierThread::send_closed_connection_notif(ClientHandler* client){
  if (continue_sending)
    blocking_queue.push(new ClosedConnectionNotification(client));
}
