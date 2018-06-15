#include "server_RadiocontrolledNotification.h"

RadiocontrolledNotification::RadiocontrolledNotification(ClientHandler* client,\
                                                size_t id, int x, int y){
  this->client = client;
  this->id = id;
  this->x = x;
  this->y = y;
}

void RadiocontrolledNotification::run(){
  client->send_radiocontrolled_info(id, x, y);
}
