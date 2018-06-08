#ifndef __STOPMOVINGEVENT__
#define __STOPMOVINGEVENT__

#include "server_IEvent.h"
#include "server_Worm.h"

class StopMovingEvent : public IEvent {
private:
    Worm* worm;
    StopMovingEvent(const StopMovingEvent&) = delete;
    StopMovingEvent& operator=(const StopMovingEvent&) = delete;
public:
    explicit StopMovingEvent(Worm* worm);

    void run();

    ~StopMovingEvent() = default;
};


#endif //__STOPMOVINGEVENT__
