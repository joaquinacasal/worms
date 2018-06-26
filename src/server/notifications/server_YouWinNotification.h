#ifndef __YOUWINNOTIFICATION__
#define __YOUWINNOTIFICATION__

#include "server_INotification.h"

/*
 * Hereda de INotification. Envía la notificación al jugador que ganó.
 */
class YouWinNotification : public INotification {
private:
    ClientHandler* client;

    YouWinNotification(const YouWinNotification&) = delete;
    YouWinNotification& operator=(const YouWinNotification&) = delete;
public:
    explicit YouWinNotification(ClientHandler* client);

    void run();

    ~YouWinNotification() = default;
};


#endif //__YOUWINNOTIFICATION__
