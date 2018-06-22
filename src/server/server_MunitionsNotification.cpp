#include "server_MunitionsNotification.h"

MunitionsNotification::MunitionsNotification(ClientHandler* client,\
            int dynamite_m, int radiocontrolled_m, int teletransportation_m){
  this->client = client;
  this->dynamite_m = dynamite_m;
  this->radiocontrolled_m = radiocontrolled_m;
  this->teletransportation_m = teletransportation_m;
}

void MunitionsNotification::run(){
  client->send_munitions_info(dynamite_m, radiocontrolled_m, teletransportation_m);
}
