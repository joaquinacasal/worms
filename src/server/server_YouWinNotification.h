#ifndef __YOUWINNOTIFICATION__
#define __YOUWINNOTIFICATION__

#include "server_INotification.h"

class YouWinNotification : public INotification {
private:
    ClientHandler* client;

    YouWinNotification(const YouWinNotification&) = delete;
    YouWinNotification& operator=(const YouWinNotification&) = delete;
public:
    YouWinNotification(ClientHandler* client);

    void run();

    ~YouWinNotification() = default;
};


#endif //__YOUWINNOTIFICATION__
