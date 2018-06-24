#include "server_EndTurnNotification.h"

EndTurnNotification::EndTurnNotification(ClientHandler* client){
  this->client = client;
}

void EndTurnNotification::run(){
  client->send_end_turn_notif();
}
