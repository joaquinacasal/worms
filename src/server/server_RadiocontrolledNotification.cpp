#include "server_RadiocontrolledNotification.h"

RadiocontrolledNotification::RadiocontrolledNotification(ClientHandler* client,\
                                                    int x, int y){
  this->client = client;
  this->x = x;
  this->y = y;
}

void RadiocontrolledNotification::run(){
  client->send_radiocontrolled_info(x, y);
}
