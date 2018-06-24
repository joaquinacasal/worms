#ifndef __DYNAMITEEVENT__
#define __DYNAMITEEVENT__

#include "server_IEvent.h"
#include "../server_Player.h"

class DynamiteEvent : public IEvent {
private:
    Player* player;
    DynamiteEvent(const DynamiteEvent&) = delete;
    DynamiteEvent& operator=(const DynamiteEvent&) = delete;
public:
    explicit DynamiteEvent(Player* player);

    void run();

    ~DynamiteEvent() = default;
};


#endif //__JUMPBACKWARDEVENT__
