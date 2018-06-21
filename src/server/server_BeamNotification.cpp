#include "server_BeamNotification.h"

BeamNotification::BeamNotification(ClientHandler* client, double x, double y, \
                                          int length, int width, int angle){
  this->client = client;
  this->x = x;
  this->y = y;
  this->length = length;
  this->width = width;
  this->angle = angle;
}

void BeamNotification::run(){
  client->send_beam_info(x, y, length, width, angle);
}
