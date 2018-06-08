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
                            int angle, bool is_facing_right){
  if (continue_sending)
    blocking_queue.push(new WormNotification(client, id, life_points, x, y, angle, is_facing_right));
}

void NotifierThread::send_stage_info(ClientHandler* client, size_t width, size_t height){
  if (continue_sending)
    blocking_queue.push(new StageNotification(client, width, height));
}

void NotifierThread::send_beam_info(ClientHandler* client, int x, int y, int length, int width, int angle){
  if (continue_sending)
    blocking_queue.push(new BeamNotification(client, x, y, length, width, angle));
}

void NotifierThread::send_dynamite_info(ClientHandler* client, int x, int y, int time_to_explosion){
  if (continue_sending)
    blocking_queue.push(new DynamiteNotification(client, x, y, time_to_explosion));
}

void NotifierThread::send_radiocontrolled_info(ClientHandler* client, int x, int y){
  if (continue_sending)
    blocking_queue.push(new RadiocontrolledNotification(client, x, y));
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
