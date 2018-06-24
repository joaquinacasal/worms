#include "server_YouWinNotification.h"

YouWinNotification::YouWinNotification(ClientHandler* client){
  this->client = client;
}

void YouWinNotification::run(){
  client->send_you_win_notif();
}
