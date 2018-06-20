#include "server_StageNotification.h"

StageNotification::StageNotification(ClientHandler* client, int width, \
                                          int height, std::string background){
  this->client = client;
  this->width = width;
  this->height = height;
  this->background = background;
}

void StageNotification::run(){
  client->send_stage_info(width, height, background);
}
