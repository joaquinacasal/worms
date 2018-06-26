#ifndef __WORMNOTIFICATION__
#define __WORMNOTIFICATION__

#include "server_INotification.h"

/*
 * Hereda de INotification. Envía información sobre un gusano.
 */
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
    bool is_the_selected_worm;

    WormNotification(const WormNotification&) = delete;
    WormNotification& operator=(const WormNotification&) = delete;
public:
    WormNotification(ClientHandler* client, size_t id, size_t life_points,\
                      double x, double y, int angle, bool is_facing_right,\
                      int team, int movement_state, bool is_the_selected_worm);

    void run();

    ~WormNotification() = default;
};


#endif //__WORMNOTIFICATION__
