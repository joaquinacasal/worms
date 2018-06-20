#include "server_WormDeathNotification.h"

WormDeathNotification::WormDeathNotification(ClientHandler* client, size_t id, int team){
  this->client = client;
  this->id = id;
  this->team = team;
}

void WormDeathNotification::run(){
  client->send_worm_death_notif(id, team);
}
