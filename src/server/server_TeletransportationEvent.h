#ifndef __TELETRANSPORTATIONEVENT__
#define __TELETRANSPORTATIONEVENT__

#include "server_IEvent.h"
#include "server_Player.h"

class TeletransportationEvent : public IEvent {
private:
    Player* player;
    double x;
    double y;

    TeletransportationEvent(const TeletransportationEvent&) = delete;
    TeletransportationEvent& operator=(const TeletransportationEvent&) = delete;
public:
    explicit TeletransportationEvent(Player* player, double x, double y);

    void run();

    ~TeletransportationEvent() = default;
};


#endif //__JUMPBACKWARDEVENT__
