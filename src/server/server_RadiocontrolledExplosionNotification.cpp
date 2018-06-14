#include "server_RadiocontrolledExplosionNotification.h"

RadiocontrolledExplosionNotification::RadiocontrolledExplosionNotification(ClientHandler* client,\
                                                size_t id){
  this->client = client;
  this->id = id;
}

void RadiocontrolledExplosionNotification::run(){
  client->send_radiocontrolled_explosion_info(id);
}
