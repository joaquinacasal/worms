#ifndef __TURNTIMENOTIFICATION__
#define __TURNTIMENOTIFICATION__

#include "server_INotification.h"

class TurnTimeNotification : public INotification {
private:
    ClientHandler* client;
    int chrono;

    TurnTimeNotification(const TurnTimeNotification&) = delete;
    TurnTimeNotification& operator=(const TurnTimeNotification&) = delete;
public:
    TurnTimeNotification(ClientHandler* client, int chrono);

    void run();

    ~TurnTimeNotification() = default;
};


#endif //__TURNTIMENOTIFICATION__
