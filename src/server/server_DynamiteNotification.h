#ifndef __DYNAMITENOTIFICATION__
#define __DYNAMITENOTIFICATION__

#include "server_INotification.h"

class DynamiteNotification : public INotification {
private:
    ClientHandler* client;
    int x;
    int y;
    int time_to_explosion;

    DynamiteNotification(const DynamiteNotification&) = delete;
    DynamiteNotification& operator=(const DynamiteNotification&) = delete;
public:
    DynamiteNotification(ClientHandler* client, int x, int y, \
                                                    int time_to_explosion);

    void run();

    ~DynamiteNotification() = default;
};


#endif //__DYNAMITENOTIFICATION__
