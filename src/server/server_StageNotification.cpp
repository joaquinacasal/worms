#include "server_StageNotification.h"

StageNotification::StageNotification(ClientHandler* client, int width, \
                                                int height){
  this->client = client;
  this->width = width;
  this->height = height;
}

void StageNotification::run(){
  client->send_stage_info(width, height);
}
