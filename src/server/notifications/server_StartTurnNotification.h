#ifndef __STARTTURNNOTIFICATION__
#define __STARTTURNNOTIFICATION__

#include "server_INotification.h"

/*
 * Hereda de INotification. Envía información sobre el inicio de un turno.
 */
class StartTurnNotification : public INotification {
private:
    ClientHandler* client;

    StartTurnNotification(const StartTurnNotification&) = delete;
    StartTurnNotification& operator=(const StartTurnNotification&) = delete;
public:
    explicit StartTurnNotification(ClientHandler* client);

    void run();

    ~StartTurnNotification() = default;
};


#endif //__STARTTURNNOTIFICATION__
