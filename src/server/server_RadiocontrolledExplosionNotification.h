#ifndef __RADIOCONTROLLEDEXPLOSIONNOTIFICATION__
#define __RADIOCONTROLLEDEXPLOSIONNOTIFICATION__

#include "server_INotification.h"

class RadiocontrolledExplosionNotification : public INotification {
private:
    ClientHandler* client;
    size_t id;

    RadiocontrolledExplosionNotification(const RadiocontrolledExplosionNotification&) = delete;
    RadiocontrolledExplosionNotification& operator=(const RadiocontrolledExplosionNotification&) = delete;
public:
    RadiocontrolledExplosionNotification(ClientHandler* client, size_t id);

    void run();

    ~RadiocontrolledExplosionNotification() = default;
};


#endif //__RADIOCONTROLLEDEXPLOSIONNOTIFICATION__
