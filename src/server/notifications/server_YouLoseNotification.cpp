#include "server_YouLoseNotification.h"

YouLoseNotification::YouLoseNotification(ClientHandler* client){
  this->client = client;
}

void YouLoseNotification::run(){
  client->send_you_lose_notif();
}
