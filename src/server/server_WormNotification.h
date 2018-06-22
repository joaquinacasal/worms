#ifndef __WORMNOTIFICATION__
#define __WORMNOTIFICATION__

#include "server_INotification.h"

class WormNotification : public INotification {
private:
    ClientHandler* client;
    size_t id;
    size_t life_points;
    double x;
    double y;
    int angle;
    bool is_facing_right;
    int team;
    int movement_state;

    WormNotification(const WormNotification&) = delete;
    WormNotification& operator=(const WormNotification&) = delete;
public:
    WormNotification(ClientHandler* client, size_t id, size_t life_points,\
                      double x, double y, int angle, bool is_facing_right,\
                      int team, int movement_state);

    void run();

    ~WormNotification() = default;
};


#endif //__WORMNOTIFICATION__
