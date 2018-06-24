#ifndef __ENDTURNNOTIFICATION__
#define __ENDTURNNOTIFICATION__

#include "server_INotification.h"

class EndTurnNotification : public INotification {
private:
    ClientHandler* client;

    EndTurnNotification(const EndTurnNotification&) = delete;
    EndTurnNotification& operator=(const EndTurnNotification&) = delete;
public:
    explicit EndTurnNotification(ClientHandler* client);

    void run();

    ~EndTurnNotification() = default;
};


#endif //__ENDTURNNOTIFICATION__
