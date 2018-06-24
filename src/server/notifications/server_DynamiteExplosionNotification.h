#ifndef __DYNAMITEEXPLOSIONNOTIFICATION__
#define __DYNAMITEEXPLOSIONNOTIFICATION__

#include "server_INotification.h"

class DynamiteExplosionNotification : public INotification {
private:
    ClientHandler* client;

    DynamiteExplosionNotification(const DynamiteExplosionNotification&)\
                                  = delete;
    DynamiteExplosionNotification& operator=\
                              (const DynamiteExplosionNotification&) = delete;
public:
    explicit DynamiteExplosionNotification(ClientHandler* client);

    void run();

    ~DynamiteExplosionNotification() = default;
};


#endif //__DYNAMITEEXPLOSIONNOTIFICATION__
