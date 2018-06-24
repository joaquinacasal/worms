#ifndef __JUMPBACKWARDEVENT__
#define __JUMPBACKWARDEVENT__

#include "server_IEvent.h"
#include "../server_Worm.h"

class JumpBackwardEvent : public IEvent {
private:
    Worm* worm;
    JumpBackwardEvent(const JumpBackwardEvent&) = delete;
    JumpBackwardEvent& operator=(const JumpBackwardEvent&) = delete;
public:
    explicit JumpBackwardEvent(Worm* worm);

    void run();

    ~JumpBackwardEvent() = default;
};


#endif //__JUMPBACKWARDEVENT__
