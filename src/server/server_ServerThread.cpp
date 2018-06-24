#include <iostream>
#include <syslog.h>
#include "server_ServerThread.h"
#include <string>
#include <vector>

#define SOCKETS_HOLDING 10

ServerThread::ServerThread(const char* port, TurnsManager& turns_manager,\
                                      GameThread& gt) :
                                                socket(port),
                                                keep_running(true),
                                                turns_manager(turns_manager),
                                                game_thread(gt){
    socket.listen(SOCKETS_HOLDING);
}

void ServerThread::run() {
    for (size_t i = 0; i < turns_manager.get_number_players() && keep_running;\
                                                                      i++){
      try {
        Socket client_socket = socket.accept();
        clients.push_back(new ClientHandler( \
                         turns_manager.get_selected_player(),\
                         std::move(client_socket)));
        turns_manager.finish_turn();
      } catch (std::exception& ex){
          syslog(LOG_ERR, "%s", ex.what());
          if (!keep_running){
              return;
          }
      }
    }
    game_thread.start();
    notifier.start();
}

void ServerThread::start_clients(){
  for (size_t i = 0; i < clients.size(); ++i) {
      clients[i]->start();
  }
  if (clients.size() > 0) clients[0]->enable_queue();
}

void ServerThread::stop(){
    keep_running = false;
    if (game_thread.was_connected()){
      notifier.stop();
      notifier.join();
    }
    for (size_t i = 0; i < clients.size(); ++i) {
        if (clients[i]->is_alive()) {
          clients[i]->stop();
          clients[i]->join();
        }
        delete clients[i];
    }
    clients.clear();
    socket.shutdown(SHUT_RDWR);
}

vector<ClientHandler*>* ServerThread::get_all_connected_clients(){
  return &clients;
}

void ServerThread::send_turn_time_information_to_clients(int turn_chrono){
  if (!keep_running) return;
  for (size_t i = 0; i < clients.size(); ++i){
    notifier.send_turn_time_info(clients[i], turn_chrono);
  }
}

void ServerThread::send_worm_information_to_clients(size_t id, \
                  size_t life_points, double x, double y, int angle, \
                  bool is_facing_right, int team, int movement_state){
  if (!keep_running) return;
  for (size_t i = 0; i < clients.size(); ++i){
    notifier.send_worm_info(clients[i], id, life_points, x, y, angle,\
                            is_facing_right, team, movement_state);
  }
}

void ServerThread::send_worm_death_notif_to_clients(size_t id, int team){
  if (!keep_running) return;
  for (size_t i = 0; i < clients.size(); ++i){
    notifier.send_worm_death_notif(clients[i], id, team);
  }
}

void ServerThread::send_stage_information_to_clients(int width, \
                                          int height, std::string background){
  if (!keep_running) return;
  for (size_t i = 0; i < clients.size(); ++i){
    notifier.send_stage_info(clients[i], width, height, background);
  }
}

void ServerThread::send_beam_information_to_clients(double x, double y,\
                                            int length, int width, int angle){
  if (!keep_running) return;
  for (size_t i = 0; i < clients.size(); ++i){
    notifier.send_beam_info(clients[i],x, y, length, width, angle);
  }
}

void ServerThread::send_dynamite_information_to_clients(double x, double y,\
                                        int time_to_explosion){
  if (!keep_running) return;
  for (size_t i = 0; i < clients.size(); ++i){
    notifier.send_dynamite_info(clients[i], x, y, time_to_explosion);
  }
}

void ServerThread::send_dynamite_explosion_to_clients(){
  for (size_t i = 0; i < clients.size(); ++i){
    notifier.send_dynamite_explosion_info(clients[i]);
  }
}


void ServerThread::send_radiocontrolled_information_to_clients(size_t id,\
                                                          double x, double y){
  if (!keep_running) return;
  for (size_t i = 0; i < clients.size(); ++i){
    notifier.send_radiocontrolled_info(clients[i], id, x, y);
  }
}

void ServerThread::send_radiocontrolled_explosion_to_clients(size_t id){
  if (!keep_running) return;
  for (size_t i = 0; i < clients.size(); ++i){
    notifier.send_radiocontrolled_explosion_info(clients[i], id);
  }
}

void ServerThread::send_munitions_info(int dynamite_m, int radiocontrolled_m,\
                                       int teletransportation_m){
  notifier.send_munitions_info(clients[actual_turn], dynamite_m, \
                               radiocontrolled_m, teletransportation_m);
}

void ServerThread::send_munitions_info_to_all_clients(){
  for (size_t i = 0; i < clients.size(); ++i){
    Player* actual_player = clients[i]->get_player();
    notifier.send_munitions_info(clients[i], \
                             actual_player->get_dynamite_munitions(), \
                             actual_player->get_radiocontrolled_munitions(), \
                             actual_player->get_teletransportation_munitions());
  }
}

void ServerThread::send_closed_connection_notif(){
  if (!keep_running) return;
  for (size_t i = 0; i < clients.size(); ++i){
    notifier.send_closed_connection_notif(clients[i]);
  }
}

void ServerThread::finishTurn(ClientHandler* client){
  notifier.send_end_turn_notif(client);
  client->disable_queue();
}

void ServerThread::startTurn(ClientHandler* client){
  notifier.send_start_turn_notif(client);
  client->enable_queue();
}

void ServerThread::send_you_win_notif(){
  notifier.send_you_win_notif(clients[actual_turn]);
}


void ServerThread::changeTurn(){
  if (!keep_running) return;
  finishTurn(clients[actual_turn]);
  turns_manager.finish_turn();
  Player* actual_player = turns_manager.get_selected_player();
  for (size_t i = 0; i < clients.size(); i++){
      if (clients[i]->get_player() == actual_player) actual_turn = i;
  }
  startTurn(clients[actual_turn]);
}

bool ServerThread::is_alive(){
  return keep_running;
}

ServerThread::~ServerThread(){
  if (is_alive()) this->stop();
}
