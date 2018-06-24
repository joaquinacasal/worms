#ifndef __CLOSEDCONNECTIONNOTIFICATION__
#define __CLOSEDCONNECTIONNOTIFICATION__

#include "server_INotification.h"

class ClosedConnectionNotification : public INotification {
private:
    ClientHandler* client;

    ClosedConnectionNotification(const ClosedConnectionNotification&) = delete;
    ClosedConnectionNotification& operator=\
                                (const ClosedConnectionNotification&) = delete;
public:
    explicit ClosedConnectionNotification(ClientHandler* client);

    void run();

    ~ClosedConnectionNotification() = default;
};


#endif //__CLOSEDCONNECTIONNOTIFICATION__
