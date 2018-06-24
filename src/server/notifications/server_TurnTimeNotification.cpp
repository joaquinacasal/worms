#include "server_TurnTimeNotification.h"

TurnTimeNotification::TurnTimeNotification(ClientHandler* client, int chrono){
  this->client = client;
  this->chrono = chrono;
}

void TurnTimeNotification::run(){
  client->send_turn_time_info(chrono);
}
