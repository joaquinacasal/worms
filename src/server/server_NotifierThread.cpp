#include "server_NotifierThread.h"
#include <string>

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


void NotifierThread::send_worm_info(ClientHandler* client, size_t id,\
                                    size_t life_points, double x, double y, \
                                    int angle, bool is_facing_right, int team,\
                                    int movement_state){
  if (continue_sending)
    blocking_queue.push(new WormNotification(client, id, life_points,\
                          x, y, angle, is_facing_right, team, movement_state));
}

void NotifierThread::send_worm_death_notif(ClientHandler* client, \
                                           size_t id, int team){
  if (continue_sending)
    blocking_queue.push(new WormDeathNotification(client, id, team));
}


void NotifierThread::send_stage_info(ClientHandler* client, size_t width,\
                                     size_t height, std::string background){
  if (continue_sending)
    blocking_queue.push(new StageNotification(client,\
                                              width, height, background));
}

void NotifierThread::send_beam_info(ClientHandler* client, double x,\
                                  double y, int length, int width, int angle){
  if (continue_sending)
    blocking_queue.push(new BeamNotification(client, x, y, length,\
                                             width, angle));
}

void NotifierThread::send_dynamite_info(ClientHandler* client, double x,\
                                        double y, int time_to_explosion){
  if (continue_sending)
    blocking_queue.push(new DynamiteNotification(client, x, y, \
                                                 time_to_explosion));
}

void NotifierThread::send_dynamite_explosion_info(ClientHandler* client){
  if (continue_sending)
    blocking_queue.push(new DynamiteExplosionNotification(client));
}


void NotifierThread::send_radiocontrolled_info(ClientHandler* client, \
                                               size_t id, double x, double y){
  if (continue_sending)
    blocking_queue.push(new RadiocontrolledNotification(client, id, x, y));
}

void NotifierThread::send_radiocontrolled_explosion_info(ClientHandler* client,\
                                                         size_t id){
  blocking_queue.push(new RadiocontrolledExplosionNotification(client, id));
}

void NotifierThread::send_munitions_info(ClientHandler* client, int dynamite_m,\
                              int radiocontrolled_m, int teletransportation_m){
  blocking_queue.push(new MunitionsNotification(client, dynamite_m, \
                                    radiocontrolled_m, teletransportation_m));
}


void NotifierThread::send_turn_time_info(ClientHandler* client,\
                                         int turn_chrono){
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

void NotifierThread::send_you_win_notif(ClientHandler* client){
  if (continue_sending)
    blocking_queue.push(new YouWinNotification(client));
}


void NotifierThread::send_closed_connection_notif(ClientHandler* client){
  if (continue_sending)
    blocking_queue.push(new ClosedConnectionNotification(client));
}
