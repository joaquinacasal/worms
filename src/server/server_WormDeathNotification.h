#ifndef __WORMDEATHNOTIFICATION__
#define __WORMDEATHNOTIFICATION__

#include "server_INotification.h"

class WormDeathNotification : public INotification {
private:
    ClientHandler* client;
    size_t id;

    WormDeathNotification(const WormDeathNotification&) = delete;
    WormDeathNotification& operator=(const WormDeathNotification&) = delete;
public:
    WormDeathNotification(ClientHandler* client, size_t id);

    void run();

    ~WormDeathNotification() = default;
};


#endif //__WORMDEATHNOTIFICATION__
