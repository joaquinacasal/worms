#include "server_DynamiteNotification.h"

DynamiteNotification::DynamiteNotification(ClientHandler* client, double x, double y,\
                                                int time_to_explosion){
  this->client = client;
  this->x = x;
  this->y = y;
  this->time_to_explosion = time_to_explosion;
}

void DynamiteNotification::run(){
  client->send_dynamite_info(x, y, time_to_explosion);
}
