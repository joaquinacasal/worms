#include "server_StartTurnNotification.h"

StartTurnNotification::StartTurnNotification(ClientHandler* client){
  this->client = client;
}

void StartTurnNotification::run(){
  client->send_start_turn_notif();
}
