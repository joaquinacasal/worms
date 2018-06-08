#include "server_WormNotification.h"

WormNotification::WormNotification(ClientHandler* client, size_t id, \
          size_t life_points, int x, int y, int angle, bool is_facing_right){
  this->client = client;
  this->id = id;
  this->life_points = life_points;
  this->x = x;
  this->y = y;
  this->angle = angle;
  this->is_facing_right = is_facing_right;
}

void WormNotification::run(){
  client->send_worm_info(id, life_points, x, y, angle, is_facing_right);
}
