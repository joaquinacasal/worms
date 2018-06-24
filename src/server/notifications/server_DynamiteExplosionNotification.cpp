#include "server_DynamiteExplosionNotification.h"

DynamiteExplosionNotification::DynamiteExplosionNotification(\
                                                      ClientHandler* client){
  this->client = client;
}

void DynamiteExplosionNotification::run(){
  client->send_dynamite_explosion_notif();
}
