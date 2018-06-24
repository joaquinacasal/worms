#include "server_ClosedConnectionNotification.h"

ClosedConnectionNotification::ClosedConnectionNotification(\
                                                    ClientHandler* client){
  this->client = client;
}

void ClosedConnectionNotification::run(){
  client->send_closed_connection_notif();
}
