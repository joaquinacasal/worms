#include "server_WormDeathNotification.h"

WormDeathNotification::WormDeathNotification(ClientHandler* client, size_t id){
  this->client = client;
  this->id = id;
}

void WormDeathNotification::run(){
  client->send_worm_death_notif(id);
}
