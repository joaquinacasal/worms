#ifndef __RADIOCONTROLLEDNOTIFICATION__
#define __RADIOCONTROLLEDNOTIFICATION__

#include "server_INotification.h"

class RadiocontrolledNotification : public INotification {
private:
    ClientHandler* client;
    int x;
    int y;

    RadiocontrolledNotification(const RadiocontrolledNotification&) = delete;
    RadiocontrolledNotification& operator=(const RadiocontrolledNotification&) = delete;
public:
    RadiocontrolledNotification(ClientHandler* client, int x, int y);

    void run();

    ~RadiocontrolledNotification() = default;
};


#endif //__RADIOCONTROLLEDNOTIFICATION__
