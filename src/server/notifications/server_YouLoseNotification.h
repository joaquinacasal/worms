#ifndef __YOULOSENOTIFICATION__
#define __YOULOSENOTIFICATION__

#include "server_INotification.h"

/*
 * Hereda de INotification. Envía la notificación al jugador que perdió.
 */
class YouLoseNotification : public INotification {
private:
    ClientHandler* client;

    YouLoseNotification(const YouLoseNotification&) = delete;
    YouLoseNotification& operator=(const YouLoseNotification&) = delete;
public:
    explicit YouLoseNotification(ClientHandler* client);

    void run();

    ~YouLoseNotification() = default;
};


#endif //__YOULOSENOTIFICATION__
